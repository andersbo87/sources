using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using System.Web;

namespace Vidly.Models
{
    public class Min18yrsIfMember : ValidationAttribute
    {
        protected override ValidationResult IsValid(object value, ValidationContext validationContext)
        {
            Customer customer = (Customer)validationContext.ObjectInstance;
            if (customer.membershipTypeId == MembershipType.unknown || customer.membershipTypeId == MembershipType.payAsYouGo)
                return ValidationResult.Success;

            if (customer.birthday == null)
                return new ValidationResult("Du må angi fødselsdato.");

            int age = DateTime.Today.Year - customer.birthday.Value.Year;

            return (age >= 18) 
                ? ValidationResult.Success 
                : new ValidationResult("Du må være 18 år eller eldre for å kunne bruke dette medlemskapet.");
        }
    }
}