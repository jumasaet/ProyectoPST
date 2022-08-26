package com.example.pstproject;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.database.sqlite.SQLiteDatabase;
import android.os.Bundle;
import android.view.View;
import android.widget.EditText;
import android.widget.Toast;

public class MainActivity4 extends AppCompatActivity {

    private EditText et14,et24,et34,et44;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main4);

        et14 = (EditText)findViewById(R.id.et14);
        et24 = (EditText)findViewById(R.id.et24);
        et34 = (EditText)findViewById(R.id.et34);
        et44 = (EditText)findViewById(R.id.et44);

    }


    public void registro(View v){
        String c1 = String.valueOf(et34.getText());
        String c2 = String.valueOf(et44.getText());
        if (((et14.getText()).length()==0) || ((et24.getText()).length()==0) || ((et34.getText()).length()==0) || ((et44.getText()).length()==0)){
            Toast.makeText(this, "Debe llenar todos los parámetros",
                    Toast.LENGTH_SHORT).show();
        } else if (!c1.equals(c2)){
            Toast.makeText(this, "Debe escribir la misma contraseña en ambos parámetros ",
                    Toast.LENGTH_SHORT).show();
        } else{
            AdminSQLiteOpenHelper admin = new AdminSQLiteOpenHelper(this,
                    "administracion", null, 1);
            SQLiteDatabase bd = admin.getWritableDatabase();
            String id = et14.getText().toString();
            String nom = et24.getText().toString();
            String p = et34.getText().toString();
            bd.execSQL("insert into usuarios (id,name,pass) values ("+id+",'"+nom+"','"+p+"')");
            //insert into estudiantes (id,nombre,contraseña) values (1316935194,'"Juan"',pepito)
            bd.close();

            Toast.makeText(this, et24.getText()+" se ha registrado con éxito",
                    Toast.LENGTH_SHORT).show();
            this.finish();
        }

    }

    public void volver(View v){
        this.finish();
    }
}