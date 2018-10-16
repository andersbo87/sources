using System.ComponentModel.DataAnnotations;

namespace Vidly.Models
{
    public class RegisterViewModel
    {
        [Required]
        [Display(Name = "Førerkort")]
        public string drivingLicense { get; set; }

        [Required]
        [StringLength(50, ErrorMessage = "{0} må bestå av mellom 1 og 50 tall", MinimumLength = 1)]
        [Display(Name = "Telefonnummer")]
        public string phone { get; set; }

        [Required]
        [EmailAddress]
        [Display(Name = "E-post")]
        public string Email { get; set; }

        [Required]
        [StringLength(100, ErrorMessage = "{0} må bestå av minst {2} tegn.", MinimumLength = 6)]
        [DataType(DataType.Password)]
        [Display(Name = "Passord")]
        public string Password { get; set; }

        [DataType(DataType.Password)]
        [Display(Name = "Bekreft passord")]
        [Compare("Password", ErrorMessage = "Passordene stemmer ikke overens.")]
        public string ConfirmPassword { get; set; }
    }
}
