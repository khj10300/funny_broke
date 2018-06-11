package project.embeded.soongsil.myapplication;

import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.view.View;
import android.webkit.WebSettings;
import android.webkit.WebView;
import android.webkit.WebViewClient;
import android.widget.Button;

public class ControllerActivity extends AppCompatActivity {

//    private VideoView videoView;
    private WebView web;
    private Button button_up;
    private Button button_down;
    private Button button_left;
    private Button button_right;
    private Button button_crain1;
    private Button button_crain2;
    private Button button_crain3;
    public Thread thread;

    public int state = 0;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_controller);

        button_up = (Button)findViewById(R.id.button_up);
        button_down = (Button)findViewById(R.id.button_down);
        button_left = (Button)findViewById(R.id.button_left);
        button_right = (Button)findViewById(R.id.button_right);
        button_crain1 = (Button)findViewById(R.id.buton_crain1);
        button_crain2 = (Button)findViewById(R.id.buton_crain2);
        button_crain3 = (Button)findViewById(R.id.buton_crain3);
     //   videoView = (VideoView)findViewById(R.id.videoview) ;
        web = (WebView)findViewById(R.id.webview);
        web.setWebViewClient(new WebViewClient());
        WebSettings setting = web.getSettings();
        setting.setJavaScriptEnabled(true);
        web.loadUrl("http://192.168.1.14:5000/video_feed");



      /*  thread = new Thread(new Runnable() {
            @Override
            public void run() {

                while(true){
                   if(state != 0){
                       SocketUtill.out.println(state);
                       state = 0;
                   }
                }
            }

        });
        thread.start();*/

     /*   Uri vidUri = Uri.parse("https://www.youtube.com/watch?v=7Rg6ilitzbI");
        MediaController mediaController = new MediaController(this);
        mediaController.setAnchorView(videoView);
        // Set video link (mp4 format )
        videoView.setMediaController(mediaController);


        videoView.setVideoURI(vidUri);
      //  videoView.requestFocus();

        videoView.setOnPreparedListener(new MediaPlayer.OnPreparedListener() {
            @Override
            public void onPrepared(MediaPlayer mp) {
                videoView.start();
            }
        });
*/
        button_up.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                state = 1;
            }
        });
        button_down.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                state = 2;
            }
        });
        button_left.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                state = 3;
            }
        });
        button_right.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                state = 4;
            }
        });
        button_crain1.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                state = 5;
            }
        });
        button_crain2.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                state = 6;
            }
        });
        button_crain3.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                state = 7;
            }
        });


    }

    @Override
    public void onBackPressed()
    {
        state = -1;
        finish();
    }


}
