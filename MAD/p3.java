package com.example.mad_programs;

import android.os.Bundle;
import android.widget.Button;
import android.widget.EditText;

import androidx.activity.EdgeToEdge;
import androidx.appcompat.app.AppCompatActivity;

public class p3 extends AppCompatActivity {
    EditText inputAmount, resultView;
    Button btnDollar, btnYen, btnPound, btnEuro;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        EdgeToEdge.enable(this);
        setContentView(R.layout.p3);

        inputAmount = findViewById(R.id.inr);
        resultView = findViewById(R.id.res);

        btnDollar = findViewById(R.id.but1);
        btnYen = findViewById(R.id.but2);
        btnPound = findViewById(R.id.but3);
        btnEuro = findViewById(R.id.but4);

        btnDollar.setOnClickListener(view -> {
            // Step A: Get the text and convert to a number
            String text = inputAmount.getText().toString();
            if (!text.isEmpty()) {
                double val = Double.parseDouble(text);

                // Step B: Calculate (1 INR = 0.012 USD)
                double result = val * 0.012;

                // Step C: Convert back to text and display
                resultView.setText(String.valueOf(result));
            }
        });

        // YEN Button
        btnYen.setOnClickListener(view -> {
            String text = inputAmount.getText().toString();
            if (!text.isEmpty()) {
                double val = Double.parseDouble(text);
                double result = val * 1.73; // 1 INR = 1.73 YEN
                resultView.setText(String.valueOf(result));
            }
        });

        // POUND Button
        btnPound.setOnClickListener(view -> {
            String text = inputAmount.getText().toString();
            if (!text.isEmpty()) {
                double val = Double.parseDouble(text);
                double result = val * 0.009; // 1 INR = 0.009 POUND
                resultView.setText(String.valueOf(result));
            }
        });

        // EURO Button
        btnEuro.setOnClickListener(view -> {
            String text = inputAmount.getText().toString();
            if (!text.isEmpty()) {
                double val = Double.parseDouble(text);
                double result = val * 0.011; // 1 INR = 0.011 EURO
                resultView.setText(String.valueOf(result));
            }
        });
    }
}
