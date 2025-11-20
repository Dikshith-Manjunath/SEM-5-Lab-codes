package com.example.mad_programs;

import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.RadioButton;
import android.widget.Toast;

import androidx.activity.EdgeToEdge;
import androidx.annotation.Nullable;
import androidx.appcompat.app.AppCompatActivity;

public class p2 extends AppCompatActivity {
    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        EdgeToEdge.enable(this);
        setContentView(R.layout.p2);

        RadioButton radiobutton1=findViewById(R.id.object1);
        RadioButton radiobutton2=findViewById(R.id.object2);
        RadioButton radiobutton3=findViewById(R.id.onject3);
        RadioButton radiobutton4=findViewById(R.id.object4);
        Button button = findViewById(R.id.btn);

        button.setOnClickListener(view-> {
                String selectedAns = "no Selection";
                if (radiobutton1.isChecked()){
                    selectedAns=radiobutton1.getText().toString();
                } else if (radiobutton2.isChecked()) {
                    selectedAns = radiobutton2.getText().toString();
                } else if (radiobutton3.isChecked()) {
                    selectedAns = radiobutton3.getText().toString();
                } else if (radiobutton4.isChecked()) {
                    selectedAns = radiobutton4.getText().toString();
                }
                if(selectedAns.equals("javascript object notation")){
                    Toast.makeText(p2.this,"Correct Answer",Toast.LENGTH_SHORT).show();
                } else
                    Toast.makeText(p2.this,"Wrong Answer", Toast.LENGTH_SHORT).show();
        });
    }
}
