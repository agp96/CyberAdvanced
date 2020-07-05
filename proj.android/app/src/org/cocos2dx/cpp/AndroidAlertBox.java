package org.cocos2dx.cpp;

import org.cocos2dx.cpp.AppActivity;
import android.app.Activity;
import android.app.AlertDialog;
public class AndroidAlertBox {
    public static void show(String text) {
        System.out.print("Java 1");
        Class activity = AppActivity.class;
        System.out.print("Java 2");
        if(AppActivity.keywordDetected == true){

        }
        System.out.print("Java 3");

    }

    static public boolean IsKeywordDetected(){
        return AppActivity.keywordDetected ;
    }
}