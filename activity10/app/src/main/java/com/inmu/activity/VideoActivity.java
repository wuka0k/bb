package com.inmu.activity;

import androidx.appcompat.app.AppCompatActivity;

import android.net.Uri;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.ImageButton;
import android.widget.VideoView;

public class VideoActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_video);

        //1.找到vv
        final VideoView vv1 = findViewById(R.id.vv1);
        vv1.setVideoURI(Uri.parse("android.resource://"+getPackageName()+"/" + R.raw.avi1));
        vv1.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                vv1.start();
            }
        });
        ImageButton b1 = findViewById(R.id.ibt_pause1);
        b1.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                vv1.pause();
            }
        });

        final VideoView vv2 = findViewById(R.id.vv2);
        vv2.setVideoURI(Uri.parse("android.resource://"+getPackageName()+"/" + R.raw.avi2));
        vv2.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                vv2.start();
            }
        });
        ImageButton b2 = findViewById(R.id.ibt_pause2);
        b2.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                vv2.pause();
            }
        });

        final VideoView vv3 = findViewById(R.id.vv3);
        vv3.setVideoURI(Uri.parse("android.resource://"+getPackageName()+"/" + R.raw.avi3));
        vv3.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                vv3.start();
            }
        });
        ImageButton b3 = findViewById(R.id.ibt_pause3);
        b3.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                vv3.pause();
            }
        });

        final VideoView vv4 = findViewById(R.id.vv4);
        vv4.setVideoURI(Uri.parse("android.resource://"+getPackageName()+"/" + R.raw.avi4));
        vv4.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                vv4.start();
            }
        });
        ImageButton b4 = findViewById(R.id.ibt_pause4);
        b4.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                vv4.pause();
            }
        });

//        final VideoView vv5 = findViewById(R.id.vv5);
//        vv5.setVideoURI(Uri.parse("android.resource://"+getPackageName()+"/" + R.raw.avi5));
//        vv5.setOnClickListener(new View.OnClickListener() {
//            @Override
//            public void onClick(View view) {
//                vv5.start();
//            }
//        });
//        ImageButton b5 = findViewById(R.id.ibt_pause5);
//        b5.setOnClickListener(new View.OnClickListener() {
//            @Override
//            public void onClick(View v) {
//                vv5.pause();
//            }
//        });
//
//        final VideoView vv6 = findViewById(R.id.vv6);
//        vv6.setVideoURI(Uri.parse("android.resource://"+getPackageName()+"/" + R.raw.avi6));
//        vv6.setOnClickListener(new View.OnClickListener() {
//            @Override
//            public void onClick(View view) {
//                vv6.start();
//            }
//        });
//        ImageButton b6 = findViewById(R.id.ibt_pause6);
//        b6.setOnClickListener(new View.OnClickListener() {
//            @Override
//            public void onClick(View v) {
//                vv6.pause();
//            }
//        });
//
//        final VideoView vv7 = findViewById(R.id.vv7);
//        vv7.setVideoURI(Uri.parse("android.resource://"+getPackageName()+"/" + R.raw.avi7));
//        vv7.setOnClickListener(new View.OnClickListener() {
//            @Override
//            public void onClick(View view) {
//                vv7.start();
//            }
//        });
//        ImageButton b7 = findViewById(R.id.ibt_pause7);
//        b7.setOnClickListener(new View.OnClickListener() {
//            @Override
//            public void onClick(View v) {
//                vv7.pause();
//            }
//        });
//
//        final VideoView vv8 = findViewById(R.id.vv8);
//        vv8.setVideoURI(Uri.parse("android.resource://"+getPackageName()+"/" + R.raw.avi8));
//        vv8.setOnClickListener(new View.OnClickListener() {
//            @Override
//            public void onClick(View view) {
//                vv8.start();
//            }
//        });
//        ImageButton b8 = findViewById(R.id.ibt_pause8);
//        b8.setOnClickListener(new View.OnClickListener() {
//            @Override
//            public void onClick(View v) {
//                vv8.pause();
//            }
//        });
    }
}
