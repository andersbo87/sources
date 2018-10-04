using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;

namespace Vidly.Models
{
    public class MembershipType
    {
        public byte id { get; set; }
        public short signUpFee { get; set; }
        public byte durationInMonths { get; set; }
        public byte discountRate { get; set; }
        public string membershipName { get; set; }

        public static readonly byte unknown = 0;
        public static readonly byte payAsYouGo = 1;
    }
}