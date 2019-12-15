package com.example.lifeexpectancy20

import android.content.Intent
import android.os.AsyncTask
import android.os.Bundle
import android.util.Log
import androidx.appcompat.app.AppCompatActivity
import androidx.recyclerview.widget.LinearLayoutManager
import androidx.recyclerview.widget.RecyclerView
import com.google.android.material.snackbar.Snackbar
import com.google.firebase.storage.FirebaseStorage
import de.siegmar.fastcsv.reader.CsvReader
import kotlinx.android.synthetic.main.activity_main.*
import java.io.File
import java.nio.charset.StandardCharsets

class MainActivity : AppCompatActivity() {

    private val countries = ArrayList<Country>()

    val storage = FirebaseStorage.getInstance()
    lateinit var dataSource: String
    lateinit var lastUpdated: String

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        val dataRef = storage.reference.child("data.csv")
        val localFile = File(baseContext.filesDir, "data")

        val coordView = coordLyt

        val dataFile = dataRef.getFile(localFile)

        dataFile.addOnSuccessListener {
            Snackbar.make(coordView, "Success", Snackbar.LENGTH_SHORT).show()
            parsing().execute(localFile)
        }.addOnFailureListener {
            Snackbar.make(coordView, "Failed", Snackbar.LENGTH_SHORT).show()
        }
    }

    internal inner class parsing : AsyncTask<File, Unit, Unit>() {
        override fun onPostExecute(result: Unit?) {
            super.onPostExecute(result)
            rvCountries.layoutManager = LinearLayoutManager(MainActivity().baseContext, RecyclerView.VERTICAL, false)
            rvCountries.adapter = CountryAdapter(countries)
        }

        override fun doInBackground(vararg p0: File?) {
            val csvReader = CsvReader()
            csvReader.setContainsHeader(true)
            csvReader.setSkipEmptyRows(true)

            val csvContainer = csvReader.read(p0[0], StandardCharsets.UTF_8)

//            Log.e("HEADER", csvContainer.header[0])

            for(row in csvContainer.rows){
//                Log.e("ROW", row.getField(0))
                val country = Country()
                country.countryName = row.getField("Country Name")
                country.serialNumber = row.originalLineNumber

                var exp = row.getField("2017")
                if(exp != ""){
                    country.currLifeExp = exp.toDouble()
                }

                country.countryCode = row.getField("Country Code")

                countries.add(country)
            }
            Log.e("SIZE", countries.size.toString())
        }
    }

}

