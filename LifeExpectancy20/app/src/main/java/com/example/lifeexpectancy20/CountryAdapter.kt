package com.example.lifeexpectancy20

import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.TextView
import androidx.recyclerview.widget.RecyclerView
import kotlinx.android.synthetic.main.item_row.view.*


class CountryAdapter(var countryList: ArrayList<Country>) : RecyclerView.Adapter<CountryAdapter.CountryHolder>() {
    override fun onCreateViewHolder(parent: ViewGroup, viewType: Int): CountryHolder {
        val inflatedView = LayoutInflater.from(parent.context).inflate(R.layout.item_row, parent, false)
        return CountryHolder(inflatedView)
    }

    override fun getItemCount(): Int = countryList.size

    override fun onBindViewHolder(holder: CountryHolder, position: Int) {
        val country = countryList[position]

        with(holder) {
            textViewName.text = country.countryName
            textViewValue.text = country.currLifeExp.toString()
        }

    }

    inner class CountryHolder(view: View) : RecyclerView.ViewHolder(view) {
        var textViewName: TextView = view.tvName
        var textViewValue: TextView = view.tvExp
    }


}