using System;
using System.Collections.Generic;
using System.Text;

namespace WeatherApp
{
    public class Weather
    {
        // Private strenger
        private string title, temperature, wind, humidity, visibility, sunrise, sunset;

        // Offentlige metoder som henter verdier
        public string getTitle()
        {
            return title;
        }

        public string getTemperature()
        {
            return temperature;
        }

        public string getWind()
        {
            return wind;
        }

        public string getHumidity()
        {
            return humidity;
        }

        public string getVisibility()
        {
            return visibility;
        }

        public string getSunrise()
        {
            return sunrise;
        }

        public string getSunset()
        {
            return sunset;
        }

        // Offentlige metoder som setter verdier:
        public void setTitle(string newTitle)
        {
            title = newTitle;
        }

        public void setTemperature(string newTemperature)
        {
            temperature = newTemperature;
        }

        public void setWind(string newWind)
        {
            wind = newWind;
        }

        public void setHumidity(string newHumidity)
        {
            humidity = newHumidity;
        }

        public void setVisibility(string newVisibility)
        {
            visibility = newVisibility;
        }

        public void setSunrise(string newSunrise)
        {
            sunrise = newSunrise;
        }

        public void setSunset(string newSunset)
        {
            sunset = newSunset;
        }

        // Konstruktør
        public Weather()
        {
            this.setTitle(" ");
            this.setTemperature(" ");
            this.setWind(" ");
            this.setHumidity(" ");
            this.setVisibility(" ");
            this.setSunrise(" ");
            this.setSunset(" ");
        }
    }
}
