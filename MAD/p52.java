package com.example.mad_programs;

import android.content.Intent;
import android.os.Bundle;
import android.widget.Button;
import androidx.appcompat.app.AppCompatActivity;

public class Second extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_second); // Make sure XML is named activity_second.xml

        // 1. Find the button
        Button btnHome = findViewById(R.id.openHomePageButton);

        // 2. Logic: Go back to the first screen (p5)
        btnHome.setOnClickListener(view -> {
            // Intent(CurrentScreen.this, DestinationScreen.class)
            Intent i = new Intent(Second.this, p5.class);
            startActivity(i);
        });
    }
}