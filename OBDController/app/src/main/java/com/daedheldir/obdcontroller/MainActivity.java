package com.daedheldir.obdcontroller;

import androidx.appcompat.app.AppCompatActivity;

import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.bluetooth.BluetoothSocket;
import android.content.Intent;
import android.os.Bundle;
import android.os.Handler;
import android.os.Looper;
import android.os.Message;
import android.util.Log;
import android.widget.Button;
import android.widget.Toast;

import java.io.IOException;
import java.util.UUID;


public class MainActivity extends AppCompatActivity {
    public final static String MODULE_MAC = "98:D3:31:F9:AB:EF";
    public final static int REQUEST_ENABLE_BT = 1;
    private static final UUID MY_UUID = UUID.fromString("00001101-0000-1000-8000-00805f9b34fb");

    BluetoothAdapter bta;                 //bluetooth stuff
    BluetoothSocket mmSocket;             //bluetooth stuff
    BluetoothDevice mmDevice;             //bluetooth stuff
    ConnectedThread btt = null;           //Our custom thread
    public Handler mHandler;              //this receives messages from thread

    boolean exhaustValveFlag = true;
    boolean exhaustPwrFlag = true;

    Button exhaustValveSwitch;
    Button exhaustPwrSwitch;
    Button exhaustCalibrationSwitch;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        exhaustValveSwitch = (Button) findViewById(R.id.exhaust_valve_button);
        exhaustPwrSwitch = (Button) findViewById(R.id.exhaust_power_button);
        exhaustCalibrationSwitch = (Button) findViewById(R.id.exhaust_calibration_button);


        exhaustValveSwitch.setOnClickListener(v -> {
            Log.i("[BLUETOOTH]", "Attempting to send data");
            if (mmSocket.isConnected() && btt != null) { //if we have connection to the bluetoothmodule
                if(exhaustValveFlag){
                    String sendtxt = "EXH_V00";
                    btt.write(sendtxt.getBytes());
                    exhaustValveFlag = false;
                    exhaustValveSwitch.setText(R.string.exhaust_valve_off);
                }else{
                    String sendtxt = "EXH_V01";
                    btt.write(sendtxt.getBytes());
                    exhaustValveFlag = true;
                    exhaustValveSwitch.setText(R.string.exhaust_valve_on);
                }

                //disable the button and wait for 4 seconds to enable it again
                exhaustValveSwitch.setEnabled(false);
                exhaustPwrSwitch.setEnabled(false);
                exhaustCalibrationSwitch.setEnabled(false);
                new Thread(new Runnable() {
                    @Override
                    public void run() {
                        try{
                            Thread.sleep(1500);
                        }catch(InterruptedException e){
                            return;
                        }

                        runOnUiThread(new Runnable() {
                            @Override
                            public void run() {
                                exhaustValveSwitch.setEnabled(true);
                                exhaustPwrSwitch.setEnabled(true);
                                exhaustCalibrationSwitch.setEnabled(true);
                            }
                        });

                    }
                }).start();
            } else {
                String msg = "Something went wrong!";
                if(!mmSocket.isConnected()) {
                    msg="Socket isn't connected! Trying to connect...";
                    attemptBTConnection();
                }else if (btt == null){
                    msg="Connected Thread is null!";
                }
                Toast.makeText(MainActivity.this, msg, Toast.LENGTH_LONG).show();
            }
        });
        exhaustPwrSwitch.setOnClickListener(v -> {
            Log.i("[BLUETOOTH]", "Attempting to send data");
            if (mmSocket.isConnected() && btt != null) { //if we have connection to the bluetoothmodule
                if(exhaustPwrFlag){
                    String sendtxt = "EXH_P00";
                    btt.write(sendtxt.getBytes());
                    exhaustPwrFlag = false;
                    exhaustPwrSwitch.setText(R.string.exhaust_pwr_off);
                }else{
                    String sendtxt = "EXH_P01";
                    btt.write(sendtxt.getBytes());
                    exhaustPwrFlag = true;
                    exhaustPwrSwitch.setText(R.string.exhaust_pwr_on);
                }

                //disable the button and wait for 4 seconds to enable it again
                exhaustValveSwitch.setEnabled(false);
                exhaustPwrSwitch.setEnabled(false);
                exhaustCalibrationSwitch.setEnabled(false);
                new Thread(new Runnable() {
                    @Override
                    public void run() {
                        try{
                            Thread.sleep(1500);
                        }catch(InterruptedException e){
                            return;
                        }

                        runOnUiThread(new Runnable() {
                            @Override
                            public void run() {
                                exhaustValveSwitch.setEnabled(true);
                                exhaustPwrSwitch.setEnabled(true);
                                exhaustCalibrationSwitch.setEnabled(true);
                            }
                        });

                    }
                }).start();
            } else {
                String msg = "Something went wrong!";
                if(!mmSocket.isConnected()) {
                    msg="Socket isn't connected! Trying to connect...";
                    attemptBTConnection();
                }else if (btt == null){
                    msg="Connected Thread is null!";
                }
                Toast.makeText(MainActivity.this, msg, Toast.LENGTH_LONG).show();
            }
        });
        exhaustCalibrationSwitch.setOnClickListener(v -> {
            Log.i("[BLUETOOTH]", "Attempting to send data");
            if (mmSocket.isConnected() && btt != null) { //if we have connection to the bluetoothmodule
                String sendtxt = "EXH_C01";
                btt.write(sendtxt.getBytes());
                exhaustCalibrationSwitch.setText(R.string.exhaust_calibration);

                //disable the button and wait for 4 seconds to enable it again
                exhaustValveSwitch.setEnabled(false);
                exhaustPwrSwitch.setEnabled(false);
                exhaustCalibrationSwitch.setEnabled(false);
                new Thread(new Runnable() {
                    @Override
                    public void run() {
                        try{
                            Thread.sleep(9000);
                        }catch(InterruptedException e){
                            return;
                        }

                        runOnUiThread(new Runnable() {
                            @Override
                            public void run() {
                                exhaustValveSwitch.setEnabled(true);
                                exhaustPwrSwitch.setEnabled(true);
                                exhaustCalibrationSwitch.setEnabled(true);
                            }
                        });

                    }
                }).start();
            } else {
                String msg = "Something went wrong!";
                if(!mmSocket.isConnected()) {
                    msg="Socket isn't connected! Trying to connect...";
                    attemptBTConnection();
                }else if (btt == null){
                    msg="Connected Thread is null!";
                }
                Toast.makeText(MainActivity.this, msg, Toast.LENGTH_LONG).show();
            }
        });

        attemptBTConnection();
    }
    private void attemptBTConnection(){
        if(bta == null)
            bta = BluetoothAdapter.getDefaultAdapter();
        //if bluetooth is not enabled then create Intent for user to turn it on
        if(!bta.isEnabled()){
            Intent enableBTIntent = new Intent(BluetoothAdapter.ACTION_REQUEST_ENABLE);
            startActivityForResult(enableBTIntent, REQUEST_ENABLE_BT);
        }else{
            initiateBluetoothProcess();
        }

    }
    @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data) {
        super.onActivityResult(requestCode, resultCode, data);
        if (resultCode == RESULT_OK && requestCode == REQUEST_ENABLE_BT) {
            initiateBluetoothProcess();
        }
    }

    public void initiateBluetoothProcess() {
        if (bta.isEnabled()) {
            //attempt to connect to bluetooth module
            BluetoothSocket tmp = null;
            mmDevice = bta.getRemoteDevice(MODULE_MAC);
            //create socket
            try {
                tmp = mmDevice.createRfcommSocketToServiceRecord(MY_UUID);
                mmSocket = tmp;
                mmSocket.connect();
                Log.i("[BLUETOOTH]", "Connected to: " + mmDevice.getName());
            } catch (IOException e) {
                Log.e("[BLUETOOTH]", "initiateBluetoothProcess: "+e.getMessage());
                try {
                    mmSocket.close();
                } catch (IOException c) {
                    return;
                }
            }
            Log.i("[BLUETOOTH]", "Creating handler");
            mHandler = new Handler(Looper.getMainLooper()) {
                @Override
                public void handleMessage(Message msg) {
                    //super.handleMessage(msg);
                    if (msg.what == ConnectedThread.RESPONSE_MESSAGE) {
                        String txt = (String) msg.obj;
                        exhaustValveSwitch.setText("\n" + txt);
                    }
                }
            };
            Log.i("[BLUETOOTH]", "Creating and running Thread");
            btt = new ConnectedThread(mmSocket, mHandler);
            btt.start();
        }
    }
}