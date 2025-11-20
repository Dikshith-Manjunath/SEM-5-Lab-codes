package com.example.mad_programs;

import android.os.Bundle;
import android.widget.Button;
import androidx.appcompat.app.AppCompatActivity;
import androidx.fragment.app.Fragment;
import androidx.fragment.app.FragmentManager;

public class p6 extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.p6);

        Button btn1 = findViewById(R.id.btn1);
        Button btn2 = findViewById(R.id.btn2);

        // 1. Load Fragment 1 by default when app starts
        if (savedInstanceState == null) {
            loadFragment(new FragmentOne());
        }

        // 2. Button Logic
        btn1.setOnClickListener(view -> loadFragment(new FragmentOne()));
        btn2.setOnClickListener(view -> loadFragment(new FragmentTwo()));
    }

    // Helper Method: The Magic Logic (Memorize this!)
    private void loadFragment(Fragment fragment) {
        FragmentManager fm = getSupportFragmentManager();
        fm.beginTransaction()
          .replace(R.id.fragmentContainer, fragment)
          .commit();
    }
}