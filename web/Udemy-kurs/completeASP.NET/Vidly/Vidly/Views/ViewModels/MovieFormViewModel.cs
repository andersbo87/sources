using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using System.Web;
using Vidly.Models;
namespace Vidly.Models.ViewModels
{
    public class MovieFormViewModel
    {
        public IEnumerable<Genre> genres { get; set; }
        public Movie movie { get; set; }
        public int? id { get; set; }

        
        [Required]
        [StringLength(255)]
        public string name { get; set; }

        [Display(Name = "Sjanger")]
        [Required]
        public byte? genreId { get; set; }

        [Display(Name = "Utgivelsesdato")]
        [Required]
        public DateTime releaseDate { get; set; }

        [Display(Name = "Antall på lager")]
        [Required]
        public byte? numbersInStock { get; set; }

        public string title
        {
            get
            {
                return id != 0 ? "Rediger film" : "Ny film";
            }
        }
        
        public MovieFormViewModel()
        {
            id = 0;
            numbersInStock = 0;
        }
        public MovieFormViewModel(Movie movie)
        {
            id = movie.id;
            name = movie.name;
            genreId = movie.genreId;
            releaseDate = movie.releaseDate;
            numbersInStock = movie.numberInStock;
        }
    }
}