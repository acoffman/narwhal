class InitialMigration < ActiveRecord::Migration
  def self.up

    create_table :users do |t|
      t.string :username
      t.string :password
      t.string :ip
    end

    create_table :blockeds do |t|
      t.integer :userid
      t.string :ip
      t.string :port
      t.string :protocol
    end

  end

  def self.down
    drop_table :blockeds
    drop_table :users

  end
end

