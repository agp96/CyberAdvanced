package org.cocos2dx.cpp;

import android.content.Context;
import android.os.Bundle;
import android.support.annotation.NonNull;
import android.support.annotation.Nullable;
import android.util.Log;

import org.cocos2dx.lib.Cocos2dxGLSurfaceView;

import java.util.List;

public class SpeechRecognitionManager implements RecognitionCallback {

    static String keyword;
    static boolean isKeywordDetected = false;
    private static String ACTIVATION_KEYWORD = "menú";
    private static final int RECORD_AUDIO_REQUEST_CODE = 101;
    String[] keywords = {"menu", "play", "options", "return", "credits","exit","music","sounds","vibration","finish turn"};

    private ContinuosRecognitionManager recognitionManager;

    public SpeechRecognitionManager(Context con) {

        recognitionManager = new ContinuosRecognitionManager(con, keywords, this);
        recognitionManager.createRecognizer();
    }

    static public boolean IsKeywordDetected(){
        return isKeywordDetected ;
    }

    protected void onDestroy() {
        recognitionManager.destroyRecognizer();
    }

    protected void onResume() {
            this.startRecognition();
    }

    protected void onPause() {
        this.stopRecognition();
    }

    protected void startRecognition() {
        recognitionManager.startRecognition();
    }

    protected void stopRecognition() {
        recognitionManager.stopRecognition();
    }

    private final String getErrorText(int errorCode) {
        String var10000;
        switch (errorCode) {
            case 1:
                var10000 = "Network timeout";
                break;
            case 2:
                var10000 = "Network error";
                break;
            case 3:
                var10000 = "Audio recording error";
                break;
            case 4:
                var10000 = "Error from server";
                break;
            case 5:
                var10000 = "Client side error";
                break;
            case 6:
                var10000 = "No speech input";
                break;
            case 7:
                var10000 = "No match";
                break;
            case 8:
                var10000 = "RecognitionService busy";
                break;
            case 9:
                var10000 = "Insufficient permissions";
                break;
            default:
                var10000 = "Didn't understand, please try again.";
        }

        return var10000;
    }

    @Override
    public void onBeginningOfSpeech() {
        Log.i("Recognition","onBeginningOfSpeech");
    }

    @Override
    public void onBufferReceived(@NonNull byte[] buffer) {
        Log.i("Recognition", "onBufferReceived: "+buffer);
    }

    @Override
    public void onEndOfSpeech() {
        Log.i("Recognition","onEndOfSpeech");
    }

    @Override
    public void onError(int errorCode) {
        String errorMessage = getErrorText(errorCode);
        Log.i("Recognition","onError: "+errorMessage);
    }

    @Override
    public void onEvent(int var1, @NonNull Bundle var2) {
        Log.i("Recognition","onEvent");
    }

    @Override
    public void onReadyForSpeech(@NonNull Bundle var1) {
        Log.i("Recognition","onReadyForSpeech");
    }

    @Override
    public void onRmsChanged(float var1) {

    }

    @Override
    public void onPrepared(@NonNull RecognitionStatus status) {
        if(status!=null) {
            if(status==RecognitionStatus.SUCCESS) {
                Log.i("Recognition","onPrepared: Success");
            }
            else if(status==RecognitionStatus.UNAVAILABLE) {
                Log.i("Recognition", "onPrepared: Failure or unavailable");
            }
        }
    }

    @Override
    public void onKeywordDetected(final String activationKeyword) {
        isKeywordDetected = true;
        keyword = activationKeyword;
        Log.i("App","keyword detected !!! "+activationKeyword);
        Cocos2dxGLSurfaceView.getInstance().queueEvent(new Runnable() {
            @Override
            public void run() {
                callCppCallback(activationKeyword);
            }
        });
    }

    @Override
    public void onPartialResults(@NonNull List var1) {

    }

    @Override
    public void onResults(@NonNull List results, @Nullable float[] var2) {
        String text = results.toString();
        Log.i("Recognition","onResults : "+text);
    }

    public native void callCppCallback(String activationKeyword);
}