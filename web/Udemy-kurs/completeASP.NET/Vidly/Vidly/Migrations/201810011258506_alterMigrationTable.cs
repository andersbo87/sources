namespace WebApplication2.Migrations
{
    using System;
    using System.Data.Entity.Migrations;
    
    public partial class alterMigrationTable : DbMigration
    {
        public override void Up()
        {
            AddColumn("dbo.MembershipTypes", "membershipName", c => c.String());
            Sql("UPDATE MembershipTypes set membershipName='Pay as You Go' WHERE id=1");
            Sql("UPDATE MembershipTypes set membershipName='Monthly' WHERE id=2");
            Sql("UPDATE MembershipTypes set membershipName='Quarterly' WHERE id=3");
            Sql("UPDATE MembershipTypes set membershipName='Annual' WHERE id=4");
        }
        
        public override void Down()
        {
            DropColumn("dbo.MembershipTypes", "membershipName");
        }
    }
}
