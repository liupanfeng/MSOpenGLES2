package com.meishe.msopengles2;

import androidx.appcompat.app.AppCompatActivity;

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

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        binding = ActivityMainBinding.inflate(getLayoutInflater());
        setContentView(binding.getRoot());

    }


    public void onRenderEffectClick(View view) {
        startActivity(new Intent(LaunchActivity.this,MSRenderEffectActivity.class));
    }
}