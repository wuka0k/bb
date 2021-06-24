package com.inmu.activity;

import android.content.DialogInterface;
import android.content.Intent;
import android.media.MediaPlayer;
import android.os.Bundle;
import android.os.Handler;
import android.util.Log;
import android.view.KeyEvent;
import android.view.MotionEvent;
import android.view.View;
import android.view.animation.Animation;
import android.view.animation.AnimationUtils;
import android.view.animation.LinearInterpolator;
import android.widget.AdapterView;
import android.widget.GridView;
import android.widget.ImageButton;
import android.widget.ImageView;
import android.widget.TextView;
import android.widget.Toast;

import androidx.appcompat.app.AlertDialog;
import androidx.appcompat.app.AppCompatActivity;
import androidx.viewpager.widget.ViewPager;

import com.inmu.activity.service.OneService;

import java.util.ArrayList;
import java.util.List;
import java.util.Timer;
import java.util.TimerTask;

public class ViewPagerActivity extends AppCompatActivity{

    public static ViewPagerActivity viewPagerActivity;
    public static Intent intent;
    long time1,time2;
    Timer timer = new Timer();
    TimerTask timerTask;
//    RelativeLayout rl;
    Handler handler;
    ViewPager viewPager;
    boolean isLoop=true;


    MediaPlayer mediaPlayer0;
    MediaPlayer mediaPlayer1;
    MediaPlayer mediaPlayer2;
    MediaPlayer mediaPlayer3;
    MediaPlayer mediaPlayer4;
    MediaPlayer mediaPlayer5;
    MediaPlayer mediaPlayer6;
    MediaPlayer mediaPlayer7;

    MediaPlayer mediaPlayerv0;
    MediaPlayer mediaPlayerv1;
    MediaPlayer mediaPlayerv2;
    MediaPlayer mediaPlayerv3;


    int[] photos = {R.mipmap.a1,R.mipmap.a2,R.mipmap.a3,R.mipmap.a4};
    String[] descriptions = {"傲慢与偏见","白鹿原","白夜行","百年孤独"};
    private List<Item2> generateData() {




        List<Item2> list = new ArrayList<Item2>();
        for (int i=0;i<4;i++){
            Item2 item2 = new Item2();
            item2.setResid(photos[i]);
            item2.setDescription((descriptions[i]));
            list.add(item2);


        }

        return list;
    }

    private List<Item2> generateData1() {
        int[] photos1 = {R.mipmap.a1,R.mipmap.a2,R.mipmap.a3,R.mipmap.a4,R.mipmap.a5,R.mipmap.a6,R.mipmap.a7,R.mipmap.a8};
        String[] descriptions1 = {"傲慢与偏见","白鹿原","白夜行","百年孤独","边城","灿烂千阳","茶花女","沉默的大多数"};

        List<Item2> list = new ArrayList<Item2>();
        for (int i=0;i<8;i++) {
            Item2 item1 = new Item2();
            item1.setResid(photos1[i]);
            item1.setDescription((descriptions1[i]));
            list.add(item1);
        }
        return list;
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main3);

        viewPagerActivity=this;

        //shang
//        rl = findViewById(R.id.rl);
//        //1.获取上一个activiyt传递过来intent对象
//        Intent intent = getIntent();
//        //2.通过intent对象获取里面的数据
//        String name = intent.getStringExtra("name");
//        String pwd = intent.getStringExtra("pwd");


        ImageButton a = findViewById(R.id.a);
        ImageButton b = findViewById(R.id.b);
        ImageButton c = findViewById(R.id.c);
        ImageButton d = findViewById(R.id.d);
        a.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Toast.makeText(ViewPagerActivity.this, "绘本馆", Toast.LENGTH_SHORT).show();
            }
        });

        b.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Toast.makeText(ViewPagerActivity.this, "录播课", Toast.LENGTH_SHORT).show();
                Intent intent1 = new Intent(ViewPagerActivity.this,VideoActivity.class);
                startActivity(intent1);
            }
        });
        c.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Toast.makeText(ViewPagerActivity.this, "排行", Toast.LENGTH_SHORT).show();
                Intent intent2 = new Intent(ViewPagerActivity.this,ListViewActivity.class);
                startActivity(intent2);
            }
        });
        d.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Toast.makeText(ViewPagerActivity.this, "我的", Toast.LENGTH_SHORT).show();
                Intent intent3 = new Intent(ViewPagerActivity.this,WodeActivity.class);
                startActivity(intent3);
            }
        });

        //zhong
        //模拟数据
        List<Item2> list = generateData();

        viewPager=findViewById(R.id.view_pager);
        Mydapter3 mydapter3 = new Mydapter3(this, list);
        viewPager.setAdapter(mydapter3);
        viewPager.setCurrentItem(1000*4);

//        handler= new Handler();
//        handler.postDelayed(new TimerRunnable(),3000);



        //xia
        List<Item2> list1 = generateData1();

        GridView gv = findViewById(R.id.gv);
        MyAdapter2 adapter = new MyAdapter2(this, list1);
        gv.setAdapter(adapter);
        gv.setOnItemClickListener(new AdapterView.OnItemClickListener() {
            @Override
            public void onItemClick(AdapterView<?> adapterView, View view, int i, long l) {
                TextView tv_descrip = view.findViewById(R.id.tv_descrip);
                Toast.makeText(ViewPagerActivity.this, tv_descrip.getText(), Toast.LENGTH_SHORT).show();
                if(i==0)
                {
                    mediaPlayer0 = MediaPlayer.create(ViewPagerActivity.this,R.raw.aa1);
                    mediaPlayer0.start();
                }else if (i==1){
                    mediaPlayer1 = MediaPlayer.create(ViewPagerActivity.this,R.raw.bb1);
                    mediaPlayer1.start();
                }else if (i==2){
                    mediaPlayer2 = MediaPlayer.create(ViewPagerActivity.this,R.raw.cc1);
                    mediaPlayer2.start();
                }else if (i==3){
                    mediaPlayer3 = MediaPlayer.create(ViewPagerActivity.this,R.raw.dd1);
                    mediaPlayer3.start();
                }else if (i==4){
                    mediaPlayer4 = MediaPlayer.create(ViewPagerActivity.this,R.raw.ee1);
                    mediaPlayer4.start();
                }else if (i==5){
                    mediaPlayer5 = MediaPlayer.create(ViewPagerActivity.this,R.raw.ff1);
                    mediaPlayer5.start();
                }else if (i==6){
                    mediaPlayer6 = MediaPlayer.create(ViewPagerActivity.this,R.raw.gg1);
                    mediaPlayer6.start();
                }else if (i==7){
                    mediaPlayer7 = MediaPlayer.create(ViewPagerActivity.this,R.raw.hh1);
                    mediaPlayer7.start();
                }
            }
        });



//????????????????????????????????????????????????????????????????????????????????
        timerTask = new TimerTask() {
            @Override
            public void run() {
                runOnUiThread(new Runnable() {
                    @Override
                    public void run() {
                        int currentItem = viewPager.getCurrentItem();
                        viewPager.setCurrentItem(currentItem+1);
                    }
                });
            }
        };
        timer.schedule(timerTask,2000,2000);


        viewPager.setOnTouchListener(new View.OnTouchListener() {
            @Override
            public boolean onTouch(View v, MotionEvent event) {

                switch(event.getAction()){
                    case 0:
                        time1=event.getDownTime();
                        time2=event.getEventTime();
                        timer.cancel();
                        break;
                    case 2:
                        time1=0;
                        break;
                    case 1:
                        if ((time2-time1)/100<4) {
                            int a = viewPager.getCurrentItem()%4;
//                            Toast.makeText(ViewPagerActivity.this,(event.getEventTime()-event.getDownTime())/100+"", Toast.LENGTH_SHORT).show();
                            Toast.makeText(ViewPagerActivity.this, descriptions[a], Toast.LENGTH_SHORT).show();

                            if (a == 0)
                            {
                                mediaPlayerv0 = MediaPlayer.create(ViewPagerActivity.this,R.raw.aa1);
                                mediaPlayerv0.start();
                            }else if (a == 1){
                                mediaPlayerv1 = MediaPlayer.create(ViewPagerActivity.this,R.raw.bb1);
                                mediaPlayerv1.start();
                            }else if (a == 2){
                                mediaPlayerv2 = MediaPlayer.create(ViewPagerActivity.this,R.raw.cc1);
                                mediaPlayerv2.start();
                            }else if (a == 3){
                                mediaPlayerv3 = MediaPlayer.create(ViewPagerActivity.this,R.raw.dd1);
                                mediaPlayerv3.start();
                            }
                        }
                        timer = new Timer();
                        timerTask = new TimerTask() {
                            @Override
                            public void run() {
                                runOnUiThread(new Runnable() {
                                    @Override
                                    public void run() {
                                        //手指离开屏幕
                                        int currentItem = viewPager.getCurrentItem();
                                        viewPager.setCurrentItem(currentItem+1);
                                    }
                                });
                            }
                        };
                        timer.schedule(timerTask,2000,2000);
                        break;
                }
                return false;
            }
        });



    }


//    class TimerRunnable implements Runnable{
//
//        @Override
//        public void run() {
//            int curItem = viewPager.getCurrentItem();
//            viewPager.setCurrentItem(curItem+1);
//            if (isLoop==false){
//
//                handler.removeCallbacks(this);
//
//            }else if(handler!=null&&isLoop==true){
//
//                handler.postDelayed(this,3000);
//            }
//        }
//    }


    float x1=0;
    float x2=0;
    @Override
    public boolean onTouchEvent(MotionEvent event) {

        intent = new Intent(ViewPagerActivity.this,OneService.class);
        ImageView img_add = findViewById(R.id.img_add);
        Animation rotate;
        View bg = findViewById(R.id.bg);
        //Log.e("ItemActivity",event.getAction()+"");
        switch(event.getAction()){
            case 0:
                //手指触摸到屏幕,获取用户触摸的坐标
                //Log.e("ItemActivity",event.getX()+"");
                x1 = event.getX();
                break;
            case  2:
                //手指在屏幕上滑
                x2 = event.getX();
                Log.e("ViewPagerActivity","x1:"+x1+"-x2:"+x2);

                if(x2-x1>300){
                    //Toast.makeText(ItemActivity.this,"向右滑",Toast.LENGTH_SHORT).show();
//                    bg.setBackgroundColor(0xFF000000);
                    startService(intent);
                    img_add.setVisibility(View.VISIBLE);
                    rotate = AnimationUtils.loadAnimation(this,R.anim.widget_rotate);
                    rotate.setFillAfter(true);
                    LinearInterpolator lin = new LinearInterpolator();//设置动画匀速运动
                    rotate.setInterpolator(lin);
                    img_add.startAnimation(rotate);
                }else if(x2-x1<-300){
                    //Toast.makeText(ItemActivity.this,"向左滑",Toast.LENGTH_SHORT).show();
//                    bg.setBackgroundColor(0xFFFFFFFF);
                    stopService(intent);
                    img_add.clearAnimation();
                    img_add.setVisibility(View.INVISIBLE);
                }
                break;
            case 1:
                //手指离开屏幕
                //Log.e("ItemActivity",event.getX()+"")
                break;
        }
        return super.onTouchEvent(event);
    }


    @Override
    public boolean onKeyDown(int keyCode, KeyEvent event) {

        switch(keyCode){
            case KeyEvent.KEYCODE_BACK:

                AlertDialog dialog = new AlertDialog.Builder(this)
                        .setTitle("重要提示")
                        .setMessage("亲，你确定要退出吗？")
                        .setIcon(R.mipmap.ic_launcher)
                        .setPositiveButton("残忍离开", new DialogInterface.OnClickListener() {
                            @Override
                            public void onClick(DialogInterface dialogInterface, int i) {
                                ViewPagerActivity.this.finish();
                            }
                        })
                        .setNegativeButton("再留一会", new DialogInterface.OnClickListener() {
                            @Override
                            public void onClick(DialogInterface dialogInterface, int i) {
                                dialogInterface.dismiss();
                            }
                        })
                        .create();
                dialog.show();


                break;
        }

        return true;
    }


}


