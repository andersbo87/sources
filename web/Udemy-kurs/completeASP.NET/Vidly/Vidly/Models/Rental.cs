using System;
using System.ComponentModel.DataAnnotations;
namespace Vidly.Models
{
    public class Rental
    {
        public int id { get; set; }
        [Required]
        public Customer customer { get; set; }
        [Required]
        public Movie movie { get; set; }
        public DateTime dateRented { get; set; }
        public DateTime? dateReturned { get; set; }
    }
}