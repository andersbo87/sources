namespace WebApplication2.Migrations
{
    using System;
    using System.Data.Entity.Migrations;
    
    public partial class addMovie : DbMigration
    {
        public override void Up()
        {
            CreateTable(
                "dbo.Genres",
                c => new
                    {
                        id = c.Byte(nullable: false),
                        genereName = c.String(nullable: false, maxLength: 255),
                    })
                .PrimaryKey(t => t.id);
            
            AddColumn("dbo.Movies", "genreId", c => c.Byte(nullable: false));
            AddColumn("dbo.Movies", "releaseDate", c => c.DateTime(nullable: false));
            AddColumn("dbo.Movies", "numberInStock", c => c.Byte(nullable: false));
            CreateIndex("dbo.Movies", "genreId");
            AddForeignKey("dbo.Movies", "genreId", "dbo.Genres", "id", cascadeDelete: true);
        }
        
        public override void Down()
        {
            DropForeignKey("dbo.Movies", "genreId", "dbo.Genres");
            DropIndex("dbo.Movies", new[] { "genreId" });
            DropColumn("dbo.Movies", "numberInStock");
            DropColumn("dbo.Movies", "releaseDate");
            DropColumn("dbo.Movies", "genreId");
            DropTable("dbo.Genres");
        }
    }
}
