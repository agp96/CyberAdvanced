/****************************************************************************
Copyright (c) 2015-2016 Chukong Technologies Inc.
Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/
package org.cocos2dx.cpp;

import android.Manifest;
import android.content.Context;
import android.content.pm.PackageManager;
import android.os.Bundle;
import org.cocos2dx.lib.Cocos2dxActivity;
import org.cocos2dx.lib.Cocos2dxHelper;

import android.os.Build;
import android.speech.SpeechRecognizer;
import android.support.annotation.Keep;
import android.support.annotation.NonNull;
import android.support.annotation.Nullable;
import android.support.v4.app.ActivityCompat;
import android.support.v4.content.ContextCompat;
import android.util.Log;
import android.view.WindowManager;
import android.view.WindowManager.LayoutParams;

import java.util.Arrays;
import java.util.List;

public class AppActivity extends Cocos2dxActivity implements RecognitionCallback {

    static boolean keywordDetected = false;
    private static String ACTIVATION_KEYWORD = "play";
    private static final int RECORD_AUDIO_REQUEST_CODE = 101;

    private ContinuosRecognitionManager recognitionManager;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.setEnableVirtualButton(false);
        super.onCreate(savedInstanceState);

        recognitionManager = new ContinuosRecognitionManager(this, ACTIVATION_KEYWORD, this);
        recognitionManager.createRecognizer();

        Log.i("App", "Start App");
        // Workaround in https://stackoverflow.com/questions/16283079/re-launch-of-activity-on-home-button-but-only-the-first-time/16447508
        if (!isTaskRoot()) {
            // Android launched another instance of the root activity into an existing task
            //  so just quietly finish and go away, dropping the user back into the activity
            //  at the top of the stack (ie: the last state of this task)
            // Don't need to finish it again since it's finished in super.onCreate .
            return;
        }
        // Make sure we're running on Pie or higher to change cutout mode
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.P) {
            // Enable rendering into the cutout area
            WindowManager.LayoutParams lp = getWindow().getAttributes();
            lp.layoutInDisplayCutoutMode = WindowManager.LayoutParams.LAYOUT_IN_DISPLAY_CUTOUT_MODE_SHORT_EDGES;
            getWindow().setAttributes(lp);
        }
        // DO OTHER INITIALIZATION BELOW
        if (ContextCompat.checkSelfPermission(this, Manifest.permission.RECORD_AUDIO) != PackageManager.PERMISSION_GRANTED) {
            ActivityCompat.requestPermissions(this, new String[]{Manifest.permission.RECORD_AUDIO}, RECORD_AUDIO_REQUEST_CODE);
            Log.i("App", "Permissions");
        }
    }

    protected void onDestroy() {
        recognitionManager.destroyRecognizer();
        super.onDestroy();
    }

    protected void onResume() {
        super.onResume();
        if (ContextCompat.checkSelfPermission((Context)this, "android.permission.RECORD_AUDIO") == 0) {
            this.startRecognition();
        }

    }

    protected void onPause() {
        this.stopRecognition();
        super.onPause();
    }

    private void startRecognition() {
        recognitionManager.startRecognition();
    }

    private void stopRecognition() {
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
    public void onKeywordDetected() {
        keywordDetected = true;
        Log.i("App","keyword detected !!!");
    }

    static public boolean keyword(){
        return keywordDetected;
    }

    @Override
    public void onPartialResults(@NonNull List var1) {

    }

    @Override
    public void onResults(@NonNull List results, @Nullable float[] var2) {
        String text = results.toString();
        Log.i("Recognition","onResults : "+text);
    }

    @Override
    public void onRequestPermissionsResult(int requestCode,
                                           String[] permissions, int[] grantResults) {
        switch (requestCode) {
            case RECORD_AUDIO_REQUEST_CODE: {
                // If request is cancelled, the result arrays are empty.
                if (grantResults.length > 0
                        && grantResults[0] == PackageManager.PERMISSION_GRANTED) {
                    startRecognition();
                    Log.i("App", "Start Recognition");
                    // permission was granted, yay! Do the
                    // contacts-related task you need to do.
                } else {
                    // permission denied, boo! Disable the
                    // functionality that depends on this permission.
                }
                return;
            }

            // other 'case' lines to check for other
            // permissions this app might request.
        }
    }
}
