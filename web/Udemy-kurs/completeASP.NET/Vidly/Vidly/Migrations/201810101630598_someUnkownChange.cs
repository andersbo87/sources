namespace WebApplication2.Migrations
{
    using System;
    using System.Data.Entity.Migrations;
    
    public partial class someUnkownChange : DbMigration
    {
        public override void Up()
        {
            CreateTable(
                "dbo.MembershipTypes",
                c => new
                    {
                        id = c.Byte(nullable: false),
                        signUpFee = c.Short(nullable: false),
                        durationInMonths = c.Byte(nullable: false),
                        discountRate = c.Byte(nullable: false),
                        membershipName = c.String(),
                    })
                .PrimaryKey(t => t.id);
            
            CreateTable(
                "dbo.GenreTypes",
                c => new
                    {
                        id = c.Byte(nullable: false),
                        genreName = c.String(nullable: false, maxLength: 255),
                    })
                .PrimaryKey(t => t.id);
            
            AddColumn("dbo.Customers", "isSubscribedToNewsletter", c => c.Boolean(nullable: false));
            AddColumn("dbo.Customers", "membershipTypeId", c => c.Byte(nullable: false));
            AddColumn("dbo.Customers", "birthday", c => c.DateTime());
            AddColumn("dbo.Movies", "genreTypeId", c => c.Byte(nullable: false));
            AddColumn("dbo.Movies", "dateAdded", c => c.DateTime(nullable: false));
            AddColumn("dbo.Movies", "releaseDate", c => c.DateTime(nullable: false));
            AddColumn("dbo.Movies", "numberInStock", c => c.Byte(nullable: false));
            AlterColumn("dbo.Customers", "name", c => c.String(nullable: false, maxLength: 255));
            AlterColumn("dbo.Movies", "name", c => c.String(nullable: false));
            CreateIndex("dbo.Customers", "membershipTypeId");
            CreateIndex("dbo.Movies", "genreTypeId");
            AddForeignKey("dbo.Customers", "membershipTypeId", "dbo.MembershipTypes", "id", cascadeDelete: true);
            AddForeignKey("dbo.Movies", "genreTypeId", "dbo.GenreTypes", "id", cascadeDelete: true);
        }
        
        public override void Down()
        {
            DropForeignKey("dbo.Movies", "genreTypeId", "dbo.GenreTypes");
            DropForeignKey("dbo.Customers", "membershipTypeId", "dbo.MembershipTypes");
            DropIndex("dbo.Movies", new[] { "genreTypeId" });
            DropIndex("dbo.Customers", new[] { "membershipTypeId" });
            AlterColumn("dbo.Movies", "name", c => c.String());
            AlterColumn("dbo.Customers", "name", c => c.String());
            DropColumn("dbo.Movies", "numberInStock");
            DropColumn("dbo.Movies", "releaseDate");
            DropColumn("dbo.Movies", "dateAdded");
            DropColumn("dbo.Movies", "genreTypeId");
            DropColumn("dbo.Customers", "birthday");
            DropColumn("dbo.Customers", "membershipTypeId");
            DropColumn("dbo.Customers", "isSubscribedToNewsletter");
            DropTable("dbo.GenreTypes");
            DropTable("dbo.MembershipTypes");
        }
    }
}
