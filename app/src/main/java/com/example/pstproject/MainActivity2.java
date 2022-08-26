package com.example.pstproject;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.view.View;
import android.widget.Toast;

public class MainActivity2 extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main2);
    }
    public void volver(View v){
        this.finish();
    }

    public void unlock(View v){
        Toast.makeText(this, "El candado ha sido desbloqueado ",
                Toast.LENGTH_SHORT).show();
    }

    public void locate(View v){
        Toast.makeText(this, "Petición de coordenadas enviada ",
                Toast.LENGTH_SHORT).show();
    }
}