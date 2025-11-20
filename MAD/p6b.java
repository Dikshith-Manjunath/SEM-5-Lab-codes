package com.example.mad_programs;

import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.Toast;
import androidx.fragment.app.Fragment;

public class FragmentTwo extends Fragment {

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState) {
        View view = inflater.inflate(R.layout.fragment2, container, false);

        Button btn = view.findViewById(R.id.f2_button);

        btn.setOnClickListener(v -> {
            Toast.makeText(getActivity(), "You are in Fragment 2", Toast.LENGTH_SHORT).show();
        });

        return view;
    }
}