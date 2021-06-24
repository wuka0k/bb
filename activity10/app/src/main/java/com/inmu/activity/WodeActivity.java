package com.inmu.activity;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;
import android.widget.Toast;

public class WodeActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_wode);
        Button button=findViewById(R.id.bt_tuichu);
        button.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {

//                Intent intent = new Intent(WodeActivity.this,MainActivity.class);
////                String tuichu = intent.getStringExtra("name");
//                intent.put
//                startActivity(intent);
                WodeActivity.this.finish();
                ViewPagerActivity.viewPagerActivity.finish();
                stopService(ViewPagerActivity.intent);
            }
        });
    }
}