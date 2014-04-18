package com.appli.joystick;

import java.util.regex.Matcher;
import java.util.regex.Pattern;

import android.content.Intent;
import android.os.Bundle;
import android.support.v4.app.Fragment;
import android.support.v7.app.ActionBarActivity;
import android.view.LayoutInflater;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.view.View.OnClickListener;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Toast;

public class MainActivity extends ActionBarActivity implements OnClickListener {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        Button button = (Button) findViewById(R.id.button1);
        button.setOnClickListener(this);
    }


    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.main, menu);
        return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        // Handle action bar item clicks here. The action bar will
        // automatically handle clicks on the Home/Up button, so long
        // as you specify a parent activity in AndroidManifest.xml.
        int id = item.getItemId();
        if (id == R.id.action_settings) {
            return true;
        }
        return super.onOptionsItemSelected(item);
    }

    /**
     * A placeholder fragment containing a simple view.
     */
    public static class PlaceholderFragment extends Fragment {

        public PlaceholderFragment() {
        }

        @Override
        public View onCreateView(LayoutInflater inflater, ViewGroup container,
                Bundle savedInstanceState) {
            View rootView = inflater.inflate(R.layout.fragment_main, container, false);
            return rootView;
        }
    }

	@Override
	/**
	 * Fonction qui catch l'appui sur le bouton
	 */
	public void onClick(View v) {
		final String EXTRA_IP_ADDRESS = "ip_address";
		final String EXTRA_PORT = "port";
		// TODO Auto-generated method stub
		String ipAddress;
		String error = "";
		int port;
		EditText text = (EditText) findViewById(R.id.editText1);
		EditText text1 = (EditText) findViewById(R.id.editText2);
		ipAddress = text.getText().toString();
		port = Integer.parseInt(text1.getText().toString());
		// REGEXP pour matcher une adress IP
		String ipAddressPattern = 
		        "(?:(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\.){3}(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)";

		Pattern pattern = Pattern.compile(ipAddressPattern);
		Matcher matcher = pattern.matcher(ipAddress);
		        if (matcher.find() && port >= 9000) {
		            // Lancer la vue de la manette en mode paysage
		        	// Passage des variables a l activite prochaine par l intent de l'activite actuelle
		        	Intent intent = new Intent(MainActivity.this, Controller.class);
		        	intent.putExtra(EXTRA_IP_ADDRESS, text.getText().toString());
		        	intent.putExtra(EXTRA_PORT, text1.getText().toString());
		        	// Lancement de l'activite suivante
		        	startActivity(intent);
		        }
		        else{
		            if (port < 9000) {
		            	error += "Port must be greater than 9000 ";
		            	text1.setText("");
		            }
		            else if (!matcher.find()) {
		            	error += "Bad ip Format";
		            	text.setText("");
		            }
		        	Toast toast = Toast.makeText(getApplicationContext(), error, Toast.LENGTH_SHORT);
		        	toast.show();
		        }
	}

}
