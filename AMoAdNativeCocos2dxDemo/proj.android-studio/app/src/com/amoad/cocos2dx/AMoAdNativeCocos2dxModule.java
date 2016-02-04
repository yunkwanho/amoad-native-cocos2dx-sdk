package com.amoad.cocos2dx;

import android.app.Activity;
import android.view.View;
import android.view.ViewGroup;
import android.view.ViewParent;
import android.widget.FrameLayout;

import com.amoad.AMoAdBuildConfig;
import com.amoad.AMoAdLogger;
import com.amoad.Native;

import org.cocos2dx.lib.Cocos2dxActivity;
import org.json.JSONException;
import org.json.JSONObject;

public final class AMoAdNativeCocos2dxModule {

    /**
     * 広告をロードする
     *
     * @param sid 管理画面から取得した64文字の英数字
     * @param tag 同じsidの複数広告を識別するための任意の文字列
     * @param x 広告のX座標
     * @param y 広告のY座標
     * @param width 広告の横幅
     * @param height 広告の縦幅
     */
    public static void load(String sid, String tag, int x, int y, int width, int height) {
        load(sid, tag, x, y, width, height, null);
    }

    /**
     * 広告をロードする (開発用)
     *
     * @param sid 管理画面から取得した64文字の英数字
     * @param tag 同じsidの複数広告を識別するための任意の文字列
     * @param x 広告のX座標
     * @param y 広告のY座標
     * @param width 広告の横幅
     * @param height 広告の縦幅
     * @param option 開発用
     */
    public static void load(final String sid, final String tag, final int x, final int y, final int width, final int height, String option) {
        final JSONObject json = toJson(option);
        getCurrentActivity().runOnUiThread(new Runnable() {
            @Override
            public void run() {
                Native.load(getCurrentActivity().getApplicationContext(), sid, tag, null, json);
                Native.hide(sid, tag);//初期は非表示
                View adView = Native.getView(sid, tag);
                if (adView.getParent() == null) {
                    addView(Native.getView(sid, tag), x, y, width, height);
                }
            }
        });
    }

    /**
     * 広告Viewを削除する（親ビューからremoveされます
     *
     * @param sid 管理画面から取得した64文字の英数字
     * @param tag 同じsidの複数広告を識別するための任意の文字列
     */
    public static void remove(final String sid, final String tag) {
        getCurrentActivity().runOnUiThread(new Runnable() {
            @Override
            public void run() {
                View adView = Native.getView(sid, tag);
                if (adView != null) {
                    ViewParent parent = adView.getParent();
                    if (parent instanceof ViewGroup) {
                        ((ViewGroup) parent).removeView(adView);
                    }
                    Native.disposeView(sid, tag);
                }
            }
        });
    }

    /**
     * 広告をリロード（別の広告に更新）する
     *
     * @param sid 管理画面から取得した64文字の英数字
     * @param tag 同じsidの複数広告を識別するための任意の文字列
     */
    public static void reload(final String sid, final String tag) {
        getCurrentActivity().runOnUiThread(new Runnable() {
            @Override
            public void run() {
                Native.reload(sid, tag);
            }
        });
    }

    /**
     * 広告Viewを表示する
     *
     * @param sid 管理画面から取得した64文字の英数字
     * @param tag 同じsidの複数広告を識別するための任意の文字列
     */
    public static void show(final String sid, final String tag) {
        getCurrentActivity().runOnUiThread(new Runnable() {
            @Override
            public void run() {
                Native.show(sid, tag);
            }
        });
    }

    /**
     * 広告Viewを非表示にする
     *
     * @param sid 管理画面から取得した64文字の英数字
     * @param tag 同じsidの複数広告を識別するための任意の文字列
     */
    public static void hide(final String sid, final String tag) {
        getCurrentActivity().runOnUiThread(new Runnable() {
            @Override
            public void run() {
                Native.hide(sid, tag);
            }
        });
    }

    /**
     * ローテーションを開始する
     *
     * @param sid 管理画面から取得した64文字の英数字
     * @param tag 同じsidの複数広告を識別するための任意の文字列
     * @param seconds ローテーション間隔(秒)
     */
    public static void startRotation(String sid, String tag, int seconds) {
        Native.startRotation(sid, tag, seconds);
    }

    /**
     * ローテーションを停止する
     *
     * @param sid 管理画面から取得した64文字の英数字
     * @param tag 同じsidの複数広告を識別するための任意の文字列
     */
    public static void stopRotation(String sid, String tag) {
        Native.stopRotation(sid, tag);
    }

    /**
     * 開発用
     *
     * @param htmlUrlString
     */
    public static void setHtmlUrlString(String htmlUrlString) {
        AMoAdBuildConfig.HTML_URL = htmlUrlString;
    }

    /**
     * 開発用
     *
     * @param seconds
     */
    public static void setNetworkTimeoutSeconds(int seconds) {
        Native.setNetworkTimeoutSeconds(seconds);
    }

    private static void addView(View view, int x, int y, int width, int height) {
        FrameLayout parent = getContentView();
        if (parent != null) {
            FrameLayout.LayoutParams lp = new FrameLayout.LayoutParams(width, height);
            lp.topMargin = y;
            lp.leftMargin = x;
            parent.addView(view, lp);
        }
    }

    private static FrameLayout getContentView() {
        View view = getCurrentActivity().findViewById(android.R.id.content);
        if (view instanceof FrameLayout) {
            return (FrameLayout) view;
        }
        return null;
    }

    private static Activity getCurrentActivity() {
        return (Activity) Cocos2dxActivity.getContext();
    }

    private static JSONObject toJson(String jsonString) {
        if (jsonString != null) {
            try {
                return new JSONObject(jsonString);
            } catch (JSONException e) {
                AMoAdLogger.getInstance().e(e);
            }
        }
        return null;
    }
}
