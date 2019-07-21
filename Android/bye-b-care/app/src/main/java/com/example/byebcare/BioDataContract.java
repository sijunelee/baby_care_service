package com.example.byebcare;

import android.content.Context;
import android.database.sqlite.SQLiteDatabase;
import android.database.sqlite.SQLiteOpenHelper;
import android.provider.BaseColumns;

public final class BioDataContract {

    private BioDataContract() {}

    public static class BioDataEntry implements BaseColumns {
        public static final String TABLE_NAME = "entry";
        public static final String COLUMN_NAME_TIME = "time";
        public static final String COLUMN_NAME_AMBIENT_TEMPERATURE = "atemp";
        public static final String COLUMN_NAME_BABY_TEMPERATURE = "btemp";
        public static final String COLUMN_NAME_BPM = "bpm";
    }

    private static final String SQL_CREATE_ENTRIES =
            "CREATE TABLE " + BioDataEntry.TABLE_NAME + " (" +
                    BioDataEntry._ID + "INTEGER PRIMARY KEY," +
                    BioDataEntry.COLUMN_NAME_TIME + " TEXT," +
                    BioDataEntry.COLUMN_NAME_AMBIENT_TEMPERATURE + " TEXT," +
                    BioDataEntry.COLUMN_NAME_BABY_TEMPERATURE + " TEXT," +
                    BioDataEntry.COLUMN_NAME_BPM + " TEXT)";

    private static final String SQL_DELETE_ENTRIES =
            "DROP TABLE IF EXISTS " + BioDataEntry.TABLE_NAME;


    public static class BioDataDbHelper extends SQLiteOpenHelper {

        private static BioDataDbHelper instance;

        public static synchronized BioDataDbHelper getInstance(Context context) {
            if (instance == null) {
                instance = new BioDataDbHelper(context.getApplicationContext());
            }
            return instance;
        }

        public static final int DATABASE_VERSION = 1;
        public static final String DATABASE_NAME = "BioData.db";

        public BioDataDbHelper(Context context) {
            super(context, DATABASE_NAME, null, DATABASE_VERSION);
        }

        public void onCreate(SQLiteDatabase db) {
            db.execSQL(SQL_CREATE_ENTRIES);
        }

        public void onUpgrade(SQLiteDatabase db, int oldVersion, int newVersion) {
            db.execSQL(SQL_DELETE_ENTRIES);
            onCreate(db);
        }

        public void onDowngrade(SQLiteDatabase db, int oldVersion, int newVersion) {
            onUpgrade(db, oldVersion, newVersion);
        }
    }

}

