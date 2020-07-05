package org.cocos2dx.cpp;

import android.app.Activity;
import android.content.Context;
import android.content.Intent;
import android.media.AudioManager;
import android.os.Build;
import android.os.Bundle;
import android.speech.RecognitionListener;
import android.speech.RecognizerIntent;
import android.speech.SpeechRecognizer;
import android.support.annotation.NonNull;
import android.util.Log;
import android.widget.TextView;

import java.util.ArrayList;
import java.util.List;


public class ContinuosRecognitionManager implements RecognitionListener {
    private boolean isActivated = false;
    private boolean shouldMute = false;
    private AudioManager audioManager = null;
    private SpeechRecognizer speech = null;
    private Context context;
    private String activationKeyword;
    private RecognitionCallback callback = null;
    private static final int REQUEST_CODE = 1;

    public ContinuosRecognitionManager(Context con, String actKey, RecognitionCallback cal) {
        context = con;
        activationKeyword = actKey;
        callback = cal;
        speech = SpeechRecognizer.createSpeechRecognizer(context);
        audioManager = (AudioManager)context.getSystemService(context.AUDIO_SERVICE);
    }

    private final Intent getRecognizerIntent() {
        Intent intent = new Intent(RecognizerIntent.ACTION_RECOGNIZE_SPEECH);
        intent.putExtra(RecognizerIntent.EXTRA_LANGUAGE_MODEL, RecognizerIntent.LANGUAGE_MODEL_FREE_FORM);
        intent.putExtra(RecognizerIntent.EXTRA_CALLING_PACKAGE, context.getPackageName());
        intent.putExtra(RecognizerIntent.EXTRA_MAX_RESULTS, 3);
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.M) {
            intent.putExtra(RecognizerIntent.EXTRA_PREFER_OFFLINE, true);
        }
        return intent;
    }

    public final void createRecognizer() {
        if (SpeechRecognizer.isRecognitionAvailable(this.context)) {
            speech.setRecognitionListener((RecognitionListener)this);
            callback.onPrepared(RecognitionStatus.SUCCESS);
        } else {
            callback.onPrepared(RecognitionStatus.UNAVAILABLE);
        }
    }

    public final void destroyRecognizer() {
        this.muteRecognition(false);
        speech.destroy();
    }

    public final void startRecognition() {
        speech.startListening(this.getRecognizerIntent());
    }

    public final void stopRecognition() {
        speech.stopListening();
    }

    public final void cancelRecognition() {
        speech.cancel();
    }

    private final void muteRecognition(boolean mute) {
        if (audioManager != null) {
            if (Build.VERSION.SDK_INT >= 23) {
                int flag = mute ? -100 : 100;
                audioManager.adjustStreamVolume(5, flag, 0);
                audioManager.adjustStreamVolume(4, flag, 0);
                audioManager.adjustStreamVolume(3, flag, 0);
                audioManager.adjustStreamVolume(2, flag, 0);
                audioManager.adjustStreamVolume(1, flag, 0);
            } else {
                audioManager.setStreamMute(5, mute);
                audioManager.setStreamMute(4, mute);
                audioManager.setStreamMute(3, mute);
                audioManager.setStreamMute(2, mute);
                audioManager.setStreamMute(1, mute);
            }
        }

    }

    public void onBeginningOfSpeech() {
        callback.onBeginningOfSpeech();
    }

    public void onReadyForSpeech(@NonNull Bundle params) {
        this.muteRecognition(this.shouldMute || !this.isActivated);
        callback.onReadyForSpeech(params);
    }

    public void onBufferReceived(@NonNull byte[] buffer) {
        callback.onBufferReceived(buffer);
    }

    public void onRmsChanged(float rmsdB) {
        callback.onRmsChanged(rmsdB);
    }

    public void onEndOfSpeech() {
        callback.onEndOfSpeech();
    }

    public void onError(int errorCode) {
        if (this.isActivated) {
            callback.onError(errorCode);
        }

        this.isActivated = false;
        switch(errorCode) {
            case 6:
                this.destroyRecognizer();
                this.createRecognizer();
            case 7:
            default:
                break;
            case 8:
                this.cancelRecognition();
        }

        this.startRecognition();
    }

    public void onEvent(int eventType, @NonNull Bundle params) {
        callback.onEvent(eventType, params);
    }

    public void onPartialResults(@NonNull Bundle partialResults) {
        ArrayList matches = partialResults.getStringArrayList("results_recognition");
        if (this.isActivated && matches != null) {
            callback.onPartialResults((List)matches);
        }
    }

    public void onResults(@NonNull Bundle results) {
        ArrayList matches = results.getStringArrayList("results_recognition");
        float[] scores = results.getFloatArray("confidence_scores");
        if (matches != null) {
            if (isActivated) {
                isActivated = false;
                callback.onResults((List)matches, scores);
                stopRecognition();
            } else {
                if (matches.contains(activationKeyword)) {
                    Log.i("App", "Palabra encontrada "+activationKeyword);
                    isActivated = true;
                    callback.onKeywordDetected();
                }
                startRecognition();
            }
        }
    }

}

