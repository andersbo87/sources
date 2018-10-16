using System;
using System.ComponentModel.DataAnnotations;
using Vidly.Models;

namespace Vidly.dtos
{
    public class MovieDto
    {
        public int id { get; set; }

        [Required(ErrorMessage = "Du må angi en filmtittel")]
        public string name { get; set; }

        [Required(ErrorMessage = "Vennligst angi en sjanger.")]
        public byte genreId { get; set; }

        public GenreTypeDto genreType { get; set; }

        [Required(ErrorMessage = "Du må angi en dato.")]
        public DateTime dateAdded { get; set; }
        
        public DateTime releaseDate { get; set; }

        [Range(1, 20)]
        public byte numberInStock { get; set; }
    }
}