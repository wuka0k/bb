package com.inmu.activity;

public class Item {
    private String name;
    private String content;
    private String date;
    private int resid;
    private int mipid;

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public String getContent() {
        return content;
    }

    public void setContent(String content) {
        this.content = content;
    }

    public String getAuthor() {
        return date;
    }

    public void setAuthor(String date) {
        this.date = date;
    }

    public int getResid() {
        return resid;
    }

    public void setResid(int resid) {
        this.resid = resid;
    }

    public int getmipid() {
        return mipid;
    }

    public void setmipid(int mipid) {
        this.mipid = mipid;
    }
}
