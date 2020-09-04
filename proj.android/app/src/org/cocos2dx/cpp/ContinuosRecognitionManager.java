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

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.InputStream;
import java.util.ArrayList;
import java.util.List;

public class ContinuosRecognitionManager implements RecognitionListener {
    private boolean isActivated = false;
    private boolean shouldMute = false;
    private boolean character = false;
    private int numCharacter = 0;
    private int x = 0;
    private int y = 0;
    private AudioManager audioManager = null;
    private SpeechRecognizer speech = null;
    private Context context;
    private int estado;
    private List<List<String>> activationKeywords = new ArrayList<List<String>>();;
    private RecognitionCallback callback = null;
    private static final int REQUEST_CODE = 1;

    public ContinuosRecognitionManager(Context con, int est, RecognitionCallback cal) {
        context = con;
        callback = cal;
        estado = est;
        leerFichero(con);
        speech = SpeechRecognizer.createSpeechRecognizer(context);
        audioManager = (AudioManager)context.getSystemService(context.AUDIO_SERVICE);
    }


    public void leerFichero(Context context) {

        String json = null;
        try {
            InputStream is = context.getAssets().open("SpeechRecognitionWords.json");
            int size = is.available();
            byte[] buffer = new byte[size];
            is.read(buffer);
            is.close();
            json = new String(buffer, "UTF-8");

            Log.i("Recognition", "JSON" + json);

            is.close();
            try {
                JSONObject obj = new JSONObject(json);
                JSONArray countries=obj.getJSONArray("speech");
                activationKeywords.add(new ArrayList<String>());
                activationKeywords.add(new ArrayList<String>());
                activationKeywords.add(new ArrayList<String>());
                activationKeywords.add(new ArrayList<String>());
                for (int i=0;i<countries.length();i++){
                    JSONObject jsonObject=countries.getJSONObject(i);
                    String scene = jsonObject.getString("scene");
                    String word = jsonObject.getString("word");
                    if(scene.equals("menu")) {
                        activationKeywords.get(0).add(word);
                    }
                    else if(scene.equals("options")) {
                        activationKeywords.get(1).add(word);
                    }
                    else if(scene.equals("credits")) {
                        activationKeywords.get(2).add(word);
                    }
                    else if(scene.equals("game")) {
                        activationKeywords.get(3).add(word);
                        System.out.println(word);
                    }
                }

            } catch (JSONException e) {
                e.printStackTrace();
            }
        } catch (FileNotFoundException e) {
            System.out.println("File not found");
        } catch (IOException e) {
            System.out.println("Error initializing stream");
        }
    }

    private final Intent getRecognizerIntent() {
        Intent intent = new Intent(RecognizerIntent.ACTION_RECOGNIZE_SPEECH);
        intent.putExtra(RecognizerIntent.EXTRA_LANGUAGE_MODEL, RecognizerIntent.LANGUAGE_MODEL_FREE_FORM);
        intent.putExtra(RecognizerIntent.EXTRA_CALLING_PACKAGE, context.getPackageName());
        intent.putExtra(RecognizerIntent.EXTRA_MAX_RESULTS, 3);
        intent.putExtra(RecognizerIntent.EXTRA_LANGUAGE, "en-US");
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

    public void onReadyForSpeech(@NonNull Bundle params) {;
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

    public void onResults(@NonNull Bundle results) {;
        ArrayList matches = results.getStringArrayList("results_recognition");
        float[] scores = results.getFloatArray("confidence_scores");
        estado = callback.getEstadoCallback();
        if (matches != null) {
            if (isActivated) {
                isActivated = false;
                callback.onResults((List)matches, scores);
                stopRecognition();
            } else {
                Log.i("App", "Array List 1 "+matches);
                if(estado < 3) {
                    for (int k = 0; k < matches.size(); k++) {
                        if(!isActivated) {
                            String[] s = matches.get(k).toString().split(" ");
                            for (int j = 0; j < s.length; j++) {
                                Log.i("App", "Array List 2 " + k + " " + matches.get(k).toString());
                                Log.i("App", "Array List 2 " + activationKeywords.get(estado).size());
                                for (int i = 0; i < activationKeywords.get(estado).size(); i++) {
                                    Log.i("App", "Array List 3 " + i + " " + s[j]);
                                    if (s[j].contains(activationKeywords.get(estado).get(i))) {
                                        Log.i("App", "Palabra encontrada " + activationKeywords.get(estado).get(i));
                                        isActivated = true;
                                        callback.onKeywordDetected(activationKeywords.get(estado).get(i), i, 0, 0);
                                    }
                                }
                            }
                        }
                    }
                }
                else {
                    Log.i("App", "Array List Estado 3 ");
                    for (int k = 0; k < matches.size(); k++) {
                        Log.i("App", "Array List Estado 3 ");
                        if (!isActivated) {
                            Log.i("App", "Array List Estado 3 ");
                            for (int i = 0; i < 8; i++) {
                                if (matches.contains(activationKeywords.get(estado).get(i))) {
                                    if (i == 6 || i == 7) {
                                        character = true;
                                        numCharacter = i;
                                    }
                                    Log.i("App", "Palabra encontrada " + activationKeywords.get(estado).get(i));
                                    isActivated = true;
                                    callback.onKeywordDetected(activationKeywords.get(estado).get(i), i, 0, 0);
                                }
                            }
                        }
                    }
                    for (int k = 0; k < matches.size(); k++) {
                        if (!isActivated) {
                            x = 0;
                            y = 0;
                            String[] s = matches.get(k).toString().split(" ");
                            for (int j = 0; j < s.length; j++) {
                                Log.i("App", "Array List 2 " + k + " " + matches.get(k).toString());
                                Log.i("App", "Array List 2 " + activationKeywords.get(estado).size());
                                for (int i = 6; i < activationKeywords.get(estado).size(); i++) {
                                    Log.i("App", "Array List 3 " + i + " " + s[j] + " " + activationKeywords.get(estado).get(i));
                                    if (s[j].contains(activationKeywords.get(estado).get(i))) {
                                        if (i > 7 && x == 0) {
                                            if (i < 11) {
                                                x = i - 5;
                                            } else {
                                                x = i - 12;
                                            }
                                            Log.i("App", "Array List 3 " + i + " " + x);
                                        } else if (i > 7 && x != 0 && y == 0) {
                                            if (i < 11) {
                                                y = i - 5;
                                            } else {
                                                y = i - 12;
                                            }
                                            Log.i("App", "Array List 3 " + i + " " + y);
                                        }
                                        if (x != 0 && y != 0) {
                                            Log.i("App", "Palabra encontrada "+activationKeywords.get(estado).get(i)+" "+numCharacter+" "+x+" "+y);
                                            isActivated = true;
                                            callback.onKeywordDetected(activationKeywords.get(estado).get(i), numCharacter, x, y);
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
                startRecognition();
                isActivated = false;
            }
        }
    }

    public static boolean isNumeric(String str) {
        try {
            Double.parseDouble(str);
            return true;
        } catch(NumberFormatException e){
            return false;
        }
    }
}

