using System;
using System.ComponentModel.DataAnnotations;
using Vidly.Models;

namespace Vidly.dtos
{
    public class CustomerDto
    {
        public int id { get; set; }

        [Required(ErrorMessage = "Vennligst skriv inn navnet ditt.")]
        [StringLength(255)]
        public string name { get; set; }

        public bool isSubscribedToNewsletter { get; set; }

        // Fordi byte krever en verdi, og fordi feilmeldingene er hardkodet på norsk, legger jeg inn en ekstra [Required]:
        [Required(ErrorMessage = "Vennligst velg et medlemskap.")]
        public byte membershipTypeId { get; set; }

        public MembershipTypeDto membershipType { get; set; }

        // [Min18yrsIfMember]
        public DateTime? birthday { get; set; }
    }
}