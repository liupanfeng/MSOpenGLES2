package com.meishe.msopengles2;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Context;
import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.TextView;

import com.meishe.msopengles2.databinding.ActivityMainBinding;

public class LaunchActivity extends AppCompatActivity {

    // Used to load the 'msopengles2' library on application startup.
    static {
        System.loadLibrary("msopengles");
    }

    private ActivityMainBinding binding;
    private Context mContext;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        mContext=this;
        binding = ActivityMainBinding.inflate(getLayoutInflater());
        setContentView(binding.getRoot());

    }

    public void onRenderEffectClick(View view) {
        MSRenderEffectActivity.startMSRenderEffectActivity(mContext,Constants.MS_SAMPLE_TYPE_KEY_TRIANGLE);
    }

    public void onRenderLineAndPoint(View view) {
        MSRenderEffectActivity.startMSRenderEffectActivity(mContext,Constants.MS_SAMPLE_TYPE_KEY_LINE);
    }

    public void onRenderTextureMap(View view) {
        MSRenderEffectActivity.startMSRenderEffectActivity(mContext,Constants.MS_SAMPLE_TYPE_KEY_TEXTURE_MAP);
    }

    public void onRenderRectangle(View view) {
        MSRenderEffectActivity.startMSRenderEffectActivity(mContext,Constants.MS_SAMPLE_TYPE_KEY_RECTANGLE);
    }

    public void onRenderCubeAndTextureMap(View view) {
        MSRenderEffectActivity.startMSRenderEffectActivity(mContext,Constants.MS_SAMPLE_TYPE_KEY_CUBE_TEXTURE_MAP);
    }


    public void onRenderCube(View view) {
        MSRenderEffectActivity.startMSRenderEffectActivity(mContext,Constants.MS_SAMPLE_TYPE_KEY_CUBE);
    }

    public void onRenderTextureMapCombine(View view) {
        MSRenderEffectActivity.startMSRenderEffectActivity(mContext,Constants.MS_SAMPLE_TYPE_KEY_TEXTURE_COMBINE);
    }
}