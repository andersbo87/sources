namespace WebApplication2.Migrations
{
    using System;
    using System.Data.Entity.Migrations;
    
    public partial class PopulateMembershipTypes : DbMigration
    {
        public override void Up()
        {
            Sql("INSERT INTO MembershipTypes (id, signUpFee, durationInMonths, discountRate, membershipName) VALUES (1, 0, 0, 0, 'Pay as You Go')");
            Sql("INSERT INTO MembershipTypes (id, signUpFee, durationInMonths, discountRate, membershipName) VALUES (2, 30, 1, 10, 'Monthly')");
            Sql("INSERT INTO MembershipTypes (id, signUpFee, durationInMonths, discountRate, membershipName) VALUES (3, 90, 3, 15, 'Quarterly')");
            Sql("INSERT INTO MembershipTypes (id, signUpFee, durationInMonths, discountRate, membershipName) VALUES (4, 300, 12, 20, 'Annual')");
        }
        
        public override void Down()
        {
        }
    }
}
