package com.example.mad_programs;

import android.content.Intent;
import android.net.Uri;
import android.os.Bundle;
import android.widget.Button;
import androidx.appcompat.app.AppCompatActivity;

public class p5 extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.p5); // Make sure XML is p5.xml

        Button btnNext = findViewById(R.id.nxtActButton);
        Button btnWeb = findViewById(R.id.openWebPageButton);

        // 1. EXPLICIT INTENT (Switching Screens inside your app)
        btnNext.setOnClickListener(view -> {
            // Syntax: new Intent(CurrentPage.this, NextPage.class);
            Intent i = new Intent(p5.this, Second.class);
            startActivity(i);
        });

        // 2. IMPLICIT INTENT (Opening an outside app like Browser)
        btnWeb.setOnClickListener(view -> {
            // Syntax: Parse the URL -> Create View Intent -> Start
            Uri webpage = Uri.parse("https://www.youtube.com/");
            Intent i = new Intent(Intent.ACTION_VIEW, webpage);
            startActivity(i);
        });
    }
}