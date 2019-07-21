package com.example.byebcare;

public class G {
    private static final int SECONDS = 1000;

    public static final int POLLING_FREQUENCY = 5 * SECONDS;
    public static final int SAVE_BIO_DATA_FREQUENCY = 5 * SECONDS;
    public static final int EMERGENCY_CALL_DELAY = 10 * SECONDS;

    //Intent REQUEST_TYPE
    public static final int START_POLLING = 0;
    public static final int DO_POLLING = 1;
    public static final int STOP_POLLING = 2;
    public static final int EMERGENCY_CALL_CANCELED = 3;
    public static final int EMERGENCY_CALL = 4;
    public static final int STOP_FOREGROUND_SERVICE = 5;
    public static final int SAVE_BIO_DATA = 6;

    //NOTIFICATION_TYPE
    public static final int NOTIFICATION_DEFAULT = 0;
    public static final int NOTIFICATION_EMERGENCY = 3;
    public static final int NOTIFICATION_FOREGROUND = 7;

    //NOTIFICATION_TIMEOUT
    public static final int NOTIFICATION_TIMEOUT = 2 * SECONDS;
    public static final int NOTIFICATION_EMERGENCY_TIMEOUT = 10 * SECONDS;

    //UNIQUE NOTIFICATION CHANNEL ID FOR FOREGROUND NOTIFICATION
    public static final int FOREGROUND_ID = 1;

    //
    public static final String REQUEST_TYPE = "REQUEST_TYPE";
    public static final String CHANNEL_ID = "CHANNEL_ID";
    public static final String CHANNEL_NAME = "CHANNEL_NAME";
    public static final String CHANNEL_DESCRIPTION = "CHANNEL_NAME";

    public static final String SERVER_URL = "http://192.168.43.214";
    public static final String EMERGENCY_CALL_NUMBER = "+8211212313123";
}
