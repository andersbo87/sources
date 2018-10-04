using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;

namespace Vidly.Models.ViewModels
{
    public class CustomerFormViewModel
    {
        public IEnumerable<MembershipType> membershipTypes { get; set; }
        public Customer customer { get; set; }
    }
}