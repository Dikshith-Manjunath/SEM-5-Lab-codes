package com.example.mad_programs;

import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.Toast;
import androidx.fragment.app.Fragment;

public class FragmentOne extends Fragment {

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState) {
        // 1. Inflate the layout (Turn XML into Java View)
        View view = inflater.inflate(R.layout.fragment1, container, false);

        // 2. Find views INSIDE the 'view' variable
        Button btn = view.findViewById(R.id.f1_button);

        // 3. Logic
        btn.setOnClickListener(v -> {
            // Use getActivity() instead of 'this' inside Fragments
            Toast.makeText(getActivity(), "You are in Fragment 1", Toast.LENGTH_SHORT).show();
        });

        return view;
    }
}