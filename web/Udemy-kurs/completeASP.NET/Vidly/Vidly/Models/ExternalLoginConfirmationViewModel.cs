using System.ComponentModel.DataAnnotations;

namespace Vidly.Models
{
    public class ExternalLoginConfirmationViewModel
    {
        [Required]
        [Display(Name = "Førerkort")]
        public string drivingLicense { get; set; }

        [Required]
        [Display(Name = "E-post")]
        public string Email { get; set; }

        [Required]
        [Display (Name = "Telefonnummer")]
        public string phone { get; set; }
    }
}
