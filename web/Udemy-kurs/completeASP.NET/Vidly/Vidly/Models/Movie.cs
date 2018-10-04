using System;
using System.ComponentModel.DataAnnotations;

namespace Vidly.Models
{
    public class Movie
    {
        public int id { get; set; }

        [Required(ErrorMessage = "Du må angi en filmtittel")]
        [Display(Name = "Tittel")]
        public string name { get; set; }
        
        [Display(Name = "Sjanger")]
        public Genre genre { get; set; }

        [Required(ErrorMessage = "Vennligst angi en sjanger.")]
        [Display(Name = "Sjanger")]
        public byte genreId { get; set; }

        [Required(ErrorMessage = "Du må angi en dato.")]
        [Display(Name = "Utgivelsesdato")]
        public DateTime dateAdded { get; set; }

        [Display(Name = "Utgivelsesdato")]
        public DateTime releaseDate { get; set; }

        [Display(Name = "Antall eksemplarer på lager")]
        [Range(1,20)]
        public byte numberInStock { get; set; }
    }
}