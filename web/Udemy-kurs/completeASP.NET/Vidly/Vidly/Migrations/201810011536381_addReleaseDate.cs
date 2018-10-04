namespace WebApplication2.Migrations
{
    using System;
    using System.Data.Entity.Migrations;
    
    public partial class addReleaseDate : DbMigration
    {
        public override void Up()
        {
            AddColumn("dbo.Movies", "dateAdded", c => c.DateTime(nullable: false));
        }
        
        public override void Down()
        {
            DropColumn("dbo.Movies", "dateAdded");
        }
    }
}
