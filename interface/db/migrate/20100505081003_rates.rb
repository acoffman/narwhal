class Rates < ActiveRecord::Migration
  def self.up
    create_table :rates do |t|
      t.float :avg_rate
      t.float :peak_rate
    end
  end

  def self.down
    drop_table :rates
  end
end
