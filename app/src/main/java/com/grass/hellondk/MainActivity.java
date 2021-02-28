package com.grass.hellondk;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity {

    private static final String TAG = "helloNdk";

    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("native-lib");
    }

    public int age = 20;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        // Example of a call to a native method
        TextView tv = findViewById(R.id.sample_text);
        tv.setText(stringFromJNI() +"\n"+ sayHello());

        findViewById(R.id.new_obj).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Object value = newObj(10);
                Log.i(TAG, "onClick: value: "+value);
            }
        });

        // c++调用java函数
        findViewById(R.id.c_call_java).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                c_call_java();
            }
        });
    }

    public String getAge(String name) {
        Log.i(TAG, "getAge: "+name);
        return "Hello " + name + ", I'm java method getAge";
    }

    public native void c_call_java();
    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    public native String stringFromJNI();

    public native String sayHello();

    public native Object newObj(int value);
}