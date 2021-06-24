package com.inmu.activity.service;

import android.app.Service;
import android.content.Intent;
import android.media.MediaPlayer;
import android.os.IBinder;
import android.widget.Toast;

import androidx.annotation.Nullable;

import com.inmu.activity.R;
import java.util.Timer;
import java.util.TimerTask;

public class OneService extends Service {

    public static boolean isplay;
    public static MediaPlayer media;

    @Override
    public void onCreate() {
        media = MediaPlayer.create(this, R.raw.music);
//        Toast.makeText(this, "服务启动了", Toast.LENGTH_SHORT).show();
        super.onCreate();
    }

    @Override
    public int onStartCommand(Intent intent, int flags, int startId) {
        String msg=intent.getStringExtra("msg");
        if (!media.isPlaying()) {
            media.start();
            isplay=media.isPlaying();
            Toast.makeText(this, "服务启动了", Toast.LENGTH_SHORT).show();
        }
        return super.onStartCommand(intent, flags, startId);
    }

    @Nullable
    @Override
    public IBinder onBind(Intent intent) {
        String msg=intent.getStringExtra("msg");
        Toast.makeText(this, "服务被绑定了"+msg, Toast.LENGTH_SHORT).show();
//        mTask2 = new TimerTask() {
//
//            @Override
//            public void run() {
//                Log.e("A","a");
//            }
//        };
//        mTimer2.schedule(mTask2, 1000, 5000);
        return null;
    }

    @Override
    public void onDestroy() {
        media.stop();
        isplay=media.isPlaying();
        media.release();
        super.onDestroy();
    }
}
