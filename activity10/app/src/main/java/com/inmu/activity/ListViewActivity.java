package com.inmu.activity;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.view.View;
import android.widget.AdapterView;
import android.widget.ListView;
import android.widget.TextView;
import android.widget.Toast;

import java.util.ArrayList;
import java.util.List;

public class ListViewActivity extends AppCompatActivity {

    int[] photos2 = {R.mipmap.a11,R.mipmap.a22,R.mipmap.a33,R.mipmap.a4,R.mipmap.a5,R.mipmap.a6,R.mipmap.a7,R.mipmap.a8};
    int[] photosmip = {R.mipmap.s1,R.mipmap.s2,R.mipmap.s3,R.mipmap.s4,R.mipmap.s5,R.mipmap.s6,R.mipmap.s7,R.mipmap.s8};
    String[] name2 = {"傲慢与偏见","白鹿原","白夜行","百年孤独","边城","灿烂千阳","茶花女","沉默的大多数"};
    String[] descript = {"《傲慢与偏见》是世界上经久不衰的伟大爱情小说之一。",
            "历时六年，五十万字，从黑发到白头 ，再现一个民族的秘史。",
            "我一直走在白夜里，从来就没有太阳，所以不怕失去。",
            "拉丁美洲魔幻现实主义文学的代表作，被誉为“再现拉丁美洲历史社会图景的鸿篇巨著”。",
            "一首哀婉凄美的田园牧歌，一首源自湘西边地的田园牧歌，湘西世界唯美的写意画。",
            "作者献给阿富汗女性的动人故事。关于不可宽恕的时代，不可能的友谊以及不可毁灭的爱。",
            "首部引入中国的西方文学名著，影响几代中国作家的爱情悲剧。",
            "爱智慧、爱自由、反对愚蠢，读王小波的“上头之选”！"};
    String[] date = {"简·奥斯汀","陈忠实","东野圭吾","加西亚·马尔克斯","沈从文","卡勒德·胡赛尼","小仲马","王小波"};
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_listview);

        //模拟数据
        List<Item> list = new ArrayList<Item>();
        int c;
        for (int i=0;i<8;i++){
            Item item = new Item();
            item.setName(name2[i]);
            c=i+1;
            item.setContent(descript[i]);
            item.setAuthor(date[i]);
            item.setResid(photos2[i]);
            item.setmipid(photosmip[i]);
            list.add(item);
        }


        //1.获取listview对象
        ListView listview = findViewById(R.id.lv);
        //3.创建适配器（简单布局，adnroid自带的）
        MyAdapter adapter = new MyAdapter(this,list);
        //2.给listview设置数据填充器
        listview.setAdapter(adapter);
        //4.给条目设置点击事件
        listview.setOnItemClickListener(new AdapterView.OnItemClickListener() {
            @Override
            public void onItemClick(AdapterView<?> adapterView, View view, int i, long l) {
                TextView tv_name = view.findViewById(R.id.tv_name2);
                Toast.makeText(ListViewActivity.this,tv_name.getText(),Toast.LENGTH_SHORT).show();
            }
        });
    }
}
