package com.example.pstproject;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.database.Cursor;
import android.database.sqlite.SQLiteDatabase;
import android.os.Bundle;
import android.view.View;
import android.widget.EditText;
import android.widget.Toast;

public class MainActivity extends AppCompatActivity {

    private EditText et11,et21;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        Intent i = new Intent(this,MainActivity3.class);
        startActivity(i);

        et11 = (EditText)findViewById(R.id.et11);
        et21 = (EditText)findViewById(R.id.et21);
    }

    public void login(View v){
        if (((et11.getText()).length()==0) || ((et21.getText()).length()==0)){
            Toast.makeText(this, "Debe escribir su cédula y contraseña",
                    Toast.LENGTH_SHORT).show();
        }else{
            AdminSQLiteOpenHelper admin = new AdminSQLiteOpenHelper(this,
                    "administracion", null, 1);
            SQLiteDatabase bd = admin.getReadableDatabase();
            String iden = et11.getText().toString();
            String pas = et21.getText().toString();

            Cursor fila = bd.rawQuery(
                    "select name,pass from usuarios where id=" + iden, null);
            if (fila.moveToFirst()){
                if (fila.getString(1).equals(pas)){
                    et11.setText("");
                    et21.setText("");
                    Intent i = new Intent(this, MainActivity2.class );
                    startActivity(i);
                }else{
                    Toast.makeText(this, "Cédula o contraseña erróneos",
                            Toast.LENGTH_SHORT).show();
                }
            }else{
                Toast.makeText(this, "Cédula o contraseña erróneos",
                        Toast.LENGTH_SHORT).show();
            }
        }
    }

    public void signin(View v){
        Intent i = new Intent(this, MainActivity4.class );
        startActivity(i);
    }
}