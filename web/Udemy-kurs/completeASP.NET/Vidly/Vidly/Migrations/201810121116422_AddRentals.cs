namespace WebApplication2.Migrations
{
    using System;
    using System.Data.Entity.Migrations;
    
    public partial class AddRentals : DbMigration
    {
        public override void Up()
        {
            CreateTable(
                "dbo.Rentals",
                c => new
                    {
                        id = c.Int(nullable: false, identity: true),
                        dateRented = c.DateTime(nullable: false),
                        dateReturned = c.DateTime(),
                        customer_id = c.Int(nullable: false),
                        movie_id = c.Int(nullable: false),
                    })
                .PrimaryKey(t => t.id)
                .ForeignKey("dbo.Customers", t => t.customer_id, cascadeDelete: true)
                .ForeignKey("dbo.Movies", t => t.movie_id, cascadeDelete: true)
                .Index(t => t.customer_id)
                .Index(t => t.movie_id);
            
        }
        
        public override void Down()
        {
            DropForeignKey("dbo.Rentals", "movie_id", "dbo.Movies");
            DropForeignKey("dbo.Rentals", "customer_id", "dbo.Customers");
            DropIndex("dbo.Rentals", new[] { "movie_id" });
            DropIndex("dbo.Rentals", new[] { "customer_id" });
            DropTable("dbo.Rentals");
        }
    }
}
