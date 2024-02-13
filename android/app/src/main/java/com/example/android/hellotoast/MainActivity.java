package com.example.android.hellotoast;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;
import android.widget.Toast;

public class MainActivity extends AppCompatActivity {

    private Button count,toast;
    private TextView tv;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        count = findViewById(R.id.count);
        toast = findViewById(R.id.toast);
        tv = findViewById(R.id.show_count);
    }


    @Override
    protected void onResume() {
        super.onResume();
        count.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                int i = Integer.parseInt(tv.getText().toString())+1;
                tv.setText(String.valueOf(i));
            }
        });

        toast.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Toast.makeText(getApplicationContext(),"Hello Toast!",Toast.LENGTH_SHORT).show();
            }
        });
    }
}