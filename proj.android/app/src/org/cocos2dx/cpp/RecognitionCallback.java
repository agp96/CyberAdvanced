package org.cocos2dx.cpp;

import android.os.Bundle;
import android.support.annotation.Nullable;
import android.support.annotation.NonNull;

import java.util.List;

public interface RecognitionCallback {
    void onPrepared(@NonNull RecognitionStatus var1);

    void onBeginningOfSpeech();

    void onKeywordDetected();

    void onReadyForSpeech(@NonNull Bundle var1);

    void onBufferReceived(@NonNull byte[] var1);

    void onRmsChanged(float var1);

    void onPartialResults(@NonNull List var1);

    void onResults(@NonNull List var1, @Nullable float[] var2);

    void onError(int var1);

    void onEvent(int var1, @NonNull Bundle var2);

    void onEndOfSpeech();
}
