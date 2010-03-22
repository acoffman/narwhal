class DashboardController < ApplicationController

  use_google_charts

# GET /dashboard
def index
  @page_title = "Firewall Performance Overview"
  @test_num = params[:test_num]
  @test_num ||= 55
  @nav_over = "current"
  dataset5 = GoogleChartDataset.new :data => [0,100]
  dataset6 = GoogleChartDataset.new :data => [@test_num, @test_num], :color => '0000FF', :title => 'Allowable Average Rate'
  dataset3 = GoogleChartDataset.new :data => [0,100]
  dataset4 = GoogleChartDataset.new :data => [75, 75], :color => 'FF0000', :title => 'Allowable Peak Rate'
  dataset1 = GoogleChartDataset.new :data => [0, 10, 20, 30, 40, 50, 60, 70, 80, 90, 100]
  dataset2 = GoogleChartDataset.new :data => [10, 50, 24, 10, 26, 32, 45, 43, 23, 42, 65], :color => '000000', :title => 'Traffic'
  @chart = init_chart("Incoming Traffic Average Rates", [dataset1, dataset2, dataset3, dataset4, dataset5, dataset6])
    	
	respond_to do |format|
	  format.html { render :overview }
  end
end

def edit_num
  @test_num = params[:value]
  render :text => @test_num
end

def ip
  @blocked = Blocked.new
	@protocols = Protocol.new
  @page_title = "IP Configuration"
  @nav_ip = "current"
  @userid = 1

  @blockeds= Blocked.all
  @protocols = Protocol.all

  respond_to do |format|
    format.html { render :action => 'ip' }
  end
end

# DELETE /dashboard/ip/1
def destroy
  @blocked = Blocked.find(params[:id])
  @blocked.destroy

  respond_to do |format|
    format.html { redirect_to :action => 'ip' }
  end
end

# GET /dashboard/ip/new
def new
  @blocked = Blocked.new
  @user = User.new

  respond_to do |format| 
    format.html
  end
end

# POST /dashboard
def create
  @blocked = Blocked.new(params[:blocked])
  
  respond_to do |format|
    if @blocked.save
      format.html { redirect_to :action => 'ip' }
    end
  end
end

def protocols
  @page_title = "Protocol Configuration"
  @nav_proto = "current"
  render :protocols
end

def move_item
  protocol = params[:protocol].split("_")[0]
  list = params[:protocol].split("_")[1]

  render :update do |page|
    page.remove "protocol_#{protocol}"
    page.insert_html :bottom, list, render(:partial=>"protocol", :object => protocol)
    page.visual_effect :highlight, "protocol_#{protocol}"
  end

end

private

def init_chart(title, datasets)
  data = GoogleChartData.new :datasets => datasets
  axis = GoogleChartAxis.new :axis  => [GoogleChartAxis::LEFT, GoogleChartAxis::BOTTOM]
  chart = GoogleLineChart.new :chart_type => GoogleLineChart::XY , :width => 500, :height => 300, :title => title
  chart.data = data
  chart.axis = axis
  chart
end

end
