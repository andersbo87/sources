using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using System.Web;

namespace Vidly.Models
{
    public class Customer
    {
        public int id { get; set; }

        [Required(ErrorMessage = "Vennligst skriv inn navnet ditt.")]
        [StringLength(255)]
        [Display(Name = "Navn")]
        public string name { get; set; }

        public bool isSubscribedToNewsletter { get; set; }

        public MembershipType membershipType { get; set; }

        // Fordi byte krever en verdi, og fordi feilmeldingene er hardkodet på norsk, legger jeg inn en ekstra [Required]:
        [Required(ErrorMessage = "Vennligst velg et medlemskap.")]
        [Display(Name = "Velg medlemskap")]
        public byte membershipTypeId { get; set; }

        [Display(Name = "Fødselsdag")]
        [Min18yrsIfMember]
        public DateTime? birthday { get; set; }
    }
}