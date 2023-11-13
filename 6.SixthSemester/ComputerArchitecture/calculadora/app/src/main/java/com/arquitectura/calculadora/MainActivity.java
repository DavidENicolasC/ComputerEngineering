package com.arquitectura.calculadora;

import android.annotation.SuppressLint;
import android.os.Bundle;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;

import androidx.appcompat.app.AppCompatActivity;

public class MainActivity extends AppCompatActivity {

    @SuppressLint("SetTextI18n")
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        EditText num1 = findViewById(R.id.numero1);
        EditText num2 = findViewById(R.id.numero2);

        TextView res = findViewById(R.id.resultado);

        Button suma = findViewById(R.id.suma);
        suma.setOnClickListener(v -> res.setText( suma( Float.parseFloat(num1.getText().toString()), Float.parseFloat(num2.getText().toString()) )+"" )
        );

        Button rest = findViewById(R.id.resta);
        rest.setOnClickListener(v -> res.setText( rest( Float.parseFloat(num1.getText().toString()), Float.parseFloat(num2.getText().toString()) )+"" )
        );

        Button mul = findViewById(R.id.multi);
        mul.setOnClickListener(v -> res.setText( multi( Float.parseFloat(num1.getText().toString()), Float.parseFloat(num2.getText().toString()) )+"" )
        );

        Button div = findViewById(R.id.div);
        div.setOnClickListener(v -> res.setText( div( Float.parseFloat(num1.getText().toString()), Float.parseFloat(num2.getText().toString()) )+"" )
        );
    }

    public float suma(float a, float b)
    {
        return a + b;
    }

    public float rest(float a, float b)
    {
        return a - b;
    }

    public float multi(float a, float b)
    {
        return a * b;
    }

    public float div(float a, float b)
    {
        return a / b;
    }
}