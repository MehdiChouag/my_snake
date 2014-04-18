package com.appli.joystick;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.net.InetSocketAddress;
import java.net.Socket;
import java.net.SocketAddress;

import android.content.Intent;
import android.os.AsyncTask;
import android.os.Bundle;
import android.os.Vibrator;
import android.support.v7.app.ActionBarActivity;
import android.util.Log;
import android.view.MotionEvent;
import android.widget.Toast;

/**
 * 
 * @author DAVID Flavien
 * @version 1.0
 * 
 * Creation d'une nouvelle activite pour afficher la manette et catcher les events
 * 
 */
public class Controller extends ActionBarActivity {
	final String EXTRA_IP_ADDRESS = "ip_address";
	final String EXTRA_PORT = "port";
	float posX = 0, posY = 0;
	Socket socks = null;
	Intent intent;
    String ipAddress, port;
    String msg;
    NetworkTask networkTask;
	
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.appli);

        intent = getIntent();
        if (intent != null) {
        	// Recuperation des donnes transmises par le biais de l'intent de l'activite precedente
        	ipAddress = intent.getStringExtra(EXTRA_IP_ADDRESS);
        	port = intent.getStringExtra(EXTRA_PORT);
        }
        networkTask = new NetworkTask();
        networkTask.execute();
    }

    public void onStop(Bundle savedInstanceState) {
    	this.finish();
    }
    
    /**
     * Fonction appeler pour les events sur la View
     */
    public boolean onTouchEvent(MotionEvent event)
    {
         if (event.getAction() == MotionEvent.ACTION_UP)
         	{
        	 msg = "0";
               posX = event.getX();
               posY = event.getY();
               try {
       			if ((posX >= (double)(300.0) && posX <= (double)(450.0)) && (posY >= (double)(500.0) && (double)(posY) <= 700.0)) {
       				// UP
       				msg = "1";
       			}
       			else if ((posX >= (double)(100.0) && posX <= (double)(300.0)) && (posY >= (double)(690.0) && (double)(posY) <= 850)) {
       				// LEFT
       				msg = "2";
       			}
       			else if ((posX >= (double)(450.0) && posX <= (double)(650.0)) && (posY >= (double)(690.0) && (double)(posY) <= 850.0)) {
       				// RIGHT
       				msg = "4";
       			}
       			else if ((posX >= (double)(300.0) && posX <= (double)(450.0)) && (posY >= (double)(850.0) && (double)(posY) <= 1050.0)) {
       				// DOWN
       				msg = "3";
       			}
       			else if ((posX >= (double)(1170.0) && posX <= (double)(1320.0)) && (posY >= (double)(720.0) && (double)(posY) <= 870.0)) {
       				// B
       				msg = "5";
       			}
       			else if ((posX >= (double)(1320.0) && posX <= (double)(1520.0)) && (posY >= (double)(700.0) && (double)(posY) <= 900.0)) {
       				// A
       				msg = "6";
       			}
       			if (Integer.parseInt(msg) != 0) {
       				// Envoi de la trame ssi une touche reconnue a ete appuyee
       				Log.e("e", "Sending data");
       				networkTask.SendDataToNetwork(msg);
       				Vibrator vib = (Vibrator) getApplicationContext().getSystemService(VIBRATOR_SERVICE);
       				vib.vibrate(20);
       			}
            } catch (NumberFormatException e) {
       			// TODO Auto-generated catch block
       			Toast.makeText(getBaseContext(), "ERROR 1" ,Toast.LENGTH_SHORT).show();
       			e.printStackTrace();
       		}
         }
         return false;
     }

    /**
     * 
     * @author DAVID Flavien
     * @version 1.0
     * 
     * Creation d'une classe heritant de la classe mere AsyncTask (Elle se charge de cree un thread qui lui meme se chargera de lire la coket en provenance du serveur)
     */
    public class NetworkTask extends AsyncTask<Void, byte[], Boolean> {
        Socket nsocket;
        InputStream nis;
        OutputStream nos;
        Toast t;
 
        @Override
        protected void onPreExecute() {
            Log.i("AsyncTask", "onPreExecute");
        }
 
        @Override
        // New Thread to receive return of TCP Socket
        protected Boolean doInBackground(Void... params) {
            boolean result = false;
            try {
                Log.i("AsyncTask", "doInBackground: Creating socket");
                SocketAddress sockaddr = new InetSocketAddress(ipAddress, Integer.parseInt(port));
                nsocket = new Socket();
                nsocket.connect(sockaddr);
                if (nsocket.isConnected()) { 
                    nis = nsocket.getInputStream();
                    nos = nsocket.getOutputStream();
                    Log.i("AsyncTask", "doInBackground: Socket created, streams assigned");
                    Log.i("AsyncTask", "doInBackground: Waiting for inital data...");
                    byte[] buffer = new byte[4096];
                    int read = nis.read(buffer, 0, 4096); // Blocking's read -- waiting for return of TCP socket -- According to accept socket
                    while(read != -1){
                        byte[] tempdata = new byte[read];
                        System.arraycopy(buffer, 0, tempdata, 0, read);
                        publishProgress(tempdata);
                        Log.i("AsyncTask", "doInBackground: Got some data");
                        read = nis.read(buffer, 0, 4096); // Blocking's read -- waiting for return of TCP socket
                    }
                }
            } catch (IOException e) {
                e.printStackTrace();
                Log.i("AsyncTask", "doInBackground: IOException");
                result = true;
            } catch (Exception e) {
                e.printStackTrace();
                Log.i("AsyncTask", "doInBackground: Exception");
                result = true;
            } finally {
                try {
                    nis.close();
                    nos.close();
                    nsocket.close();
                } catch (IOException e) {
                    e.printStackTrace();
                } catch (Exception e) {
                    e.printStackTrace();
                }
                Log.i("AsyncTask", "doInBackground: Finished");
            }
            return result;
        }
 
        /**
         * 
         * @param cmd
         */
        public void SendDataToNetwork(String cmd) {
            try {
                if (nsocket.isConnected()) {
                    Log.i("AsyncTask", "SendDataToNetwork: Writing received message to socket");
                    nos.write(cmd.getBytes());
                } else {
                	
                	t = Toast.makeText(getBaseContext(), "Cannot connect to server" ,Toast.LENGTH_SHORT);
                	t.show();
                    Log.i("AsyncTask", "SendDataToNetwork: Cannot send message. Socket is closed");
                }
            } catch (Exception e) {
            	t = Toast.makeText(getBaseContext(), "Message Send failed" ,Toast.LENGTH_SHORT);
            	t.show();
                Log.i("AsyncTask", "SendDataToNetwork: Message send failed. Caught an exception");
            }
        }
    }
}
