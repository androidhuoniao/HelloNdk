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

        findViewById(R.id.dynamic_register).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                text("i am text()");
                static_text("i am static_text()");
            }
        });

        findViewById(R.id.hello_array).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                int[] a = {0, 1, 2, 3, 4, 5};
                for (int i = 0; i < 6; i++) {
                    Log.i(TAG, "mmm调用前数组数据 "+a[i] + "/");
                }
                textArray(a);
                for (int i = 0; i < 6; i++) {
                    Log.i(TAG, "mmm调用后数组数据 "+a[i] + "/");
                }
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

    // 这两个函数用来学习动态注册
    public native int text(String message);
    public static native int static_text(String message);

    public native void textArray(int[] array);

}