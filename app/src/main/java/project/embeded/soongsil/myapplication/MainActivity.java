package project.embeded.soongsil.myapplication;

import android.content.Intent;
import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;

import java.io.BufferedWriter;
import java.io.IOException;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.net.Socket;

public class MainActivity extends AppCompatActivity {

    private Button button_game_start;
    public EditText edittext_ip;
    public EditText edittext_port;

    private static final String TAG = "DEBUG";
    private Thread thread;


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        button_game_start = (Button)findViewById(R.id.button_game_start);
        edittext_ip = (EditText)findViewById(R.id.edittext_ip);
        edittext_port = (EditText)findViewById(R.id.edittext_port);

        thread = new Thread(new Runnable() {
            @Override
            public void run() {
                    try {
                            SocketUtill.socket = new Socket(SocketUtill.SERVER_IP, SocketUtill.SERVER_PORT);
                            SocketUtill.out = new PrintWriter(new BufferedWriter(
                                    new OutputStreamWriter(SocketUtill.socket.getOutputStream())), true);
                            Intent intent = new Intent(getApplicationContext(), ControllerActivity.class);
                            startActivity(intent);
                            thread.interrupt();
                    } catch (IOException e) {
                        Log.e(TAG, "SOCKET Create ERROR");
                    }finally {
                        Log.e(TAG, "thread finish!");
                    }

            }
        });

        button_game_start.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
/*                Intent intent = new Intent(getApplicationContext(),BluetoothActivity.class);
                startActivity(intent);*/
                    if(!edittext_ip.getText().toString().equals("")) {
                        SocketUtill.SERVER_IP = edittext_ip.getText().toString();

                    }
                    if(!edittext_port.getText().toString().equals("")){
                        SocketUtill.SERVER_PORT = Integer.parseInt(edittext_port.getText().toString());
                    }
                    thread.start();


            }
        });
    }
}
