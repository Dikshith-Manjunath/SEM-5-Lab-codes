package com.example.mad_programs;

import android.os.Bundle;
import android.widget.Button;
import android.widget.EditText;
import androidx.appcompat.app.AppCompatActivity;

public class p4 extends AppCompatActivity {

    // 1. Declare Variables
    EditText num1, num2, result;
    Button btnAdd, btnSub, btnMul, btnDiv, btnMod;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.p4); // Make sure XML file is named p4.xml

        // 2. Initialize Views (Connect to IDs)
        num1 = findViewById(R.id.num1);
        num2 = findViewById(R.id.num2);
        result = findViewById(R.id.res);

        btnAdd = findViewById(R.id.but1);
        btnSub = findViewById(R.id.but2);
        btnMul = findViewById(R.id.but3);
        btnDiv = findViewById(R.id.but4);
        btnMod = findViewById(R.id.but5);

        // 3. The Logic (Repeated 5 times)
        
        // ADDITION (+)
        btnAdd.setOnClickListener(view -> {
            String s1 = num1.getText().toString();
            String s2 = num2.getText().toString();
            
            // Simple conversion and math
            double a = Double.parseDouble(s1);
            double b = Double.parseDouble(s2);
            double c = a + b;
            
            // Set Result
            result.setText(Double.toString(c));
        });

        // SUBTRACTION (-)
        btnSub.setOnClickListener(view -> {
            double a = Double.parseDouble(num1.getText().toString());
            double b = Double.parseDouble(num2.getText().toString());
            double c = a - b;
            result.setText(Double.toString(c));
        });

        // MULTIPLICATION (*)
        btnMul.setOnClickListener(view -> {
            double a = Double.parseDouble(num1.getText().toString());
            double b = Double.parseDouble(num2.getText().toString());
            double c = a * b;
            result.setText(Double.toString(c));
        });

        // DIVISION (/)
        btnDiv.setOnClickListener(view -> {
            double a = Double.parseDouble(num1.getText().toString());
            double b = Double.parseDouble(num2.getText().toString());
            double c = a / b;
            result.setText(Double.toString(c));
        });

        // MODULUS (%)
        btnMod.setOnClickListener(view -> {
            double a = Double.parseDouble(num1.getText().toString());
            double b = Double.parseDouble(num2.getText().toString());
            double c = a % b;
            result.setText(Double.toString(c));
        });
    }
}